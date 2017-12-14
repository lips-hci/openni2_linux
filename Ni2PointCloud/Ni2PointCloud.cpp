#include <iostream>
#include <iomanip>
#include <OpenNI.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/viz/vizcore.hpp>

using namespace std;
using namespace openni;
using namespace cv;

Mat niComputeCloud( const Mat depthMap, const VideoStream& depthStream )
{
    Size nsize = depthMap.size();
    vector<Mat> output( 3 );
    output[0] = Mat( nsize, CV_32F );
    output[1] = Mat( nsize, CV_32F );
    output[2] = Mat( nsize, CV_32F );

    const DepthPixel* pDepthArray = (const DepthPixel*)depthMap.data;

    for( int y = 0; y < depthMap.rows; y++ )
    {
        for( int x = 0; x < depthMap.cols; x++ )
        {
            float fX, fY, fZ;
            CoordinateConverter::convertDepthToWorld( depthStream,
                                                    x, y, *pDepthArray++,
                                                    &fX, &fY, &fZ );
            output[0].at<float>(y,x) = fX;
            output[1].at<float>(y,x) = fY;
            output[2].at<float>(y,x) = fZ;
        }
    }

    Mat outMat;
    merge( output, outMat );
    return outMat;
}

int main( int argc, char* argv[] )
{
    float hfov, vfov;
    Status status;

    // Create window
    viz::Viz3d myWindow( "Point Cloud" );

    if ( STATUS_OK != OpenNI::initialize() ) {
        cout << "After initialization: " << OpenNI::getExtendedError() << endl << endl;
        return 1;
    }

    Device devDevice;
    if ( STATUS_OK != devDevice.open( ANY_DEVICE) ) {
        cout << "ERROR: Cannot open device: " << OpenNI::getExtendedError() << endl << endl;
        return 1;
    }

    //Check and enable Depth-To-Color image registration
    if( !devDevice.isImageRegistrationModeSupported( IMAGE_REGISTRATION_DEPTH_TO_COLOR ) )
    {
        cout << "ERROR: ImageRegistration mode is not supported" << endl << endl;
        return 1;
    }
    devDevice.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );

    VideoMode mode;
    VideoStream vsDepth;
    VideoStream vsColor;

    if ( STATUS_OK != vsDepth.create( devDevice, SENSOR_DEPTH ) ) {
        cout << "ERROR: Cannot create depth stream on device" << endl << endl;
        return 1;
    }

    mode = vsDepth.getVideoMode();
    cout << "Depth VideoMode: " << mode.getResolutionX() << " x " << mode.getResolutionY() << " @ " << mode.getFps() << " FPS";
    cout << ", Unit is ";
    if(mode.getPixelFormat() == PIXEL_FORMAT_DEPTH_1_MM)
        cout << "1mm";
    else if (mode.getPixelFormat() == PIXEL_FORMAT_DEPTH_100_UM)
        cout << "100um";
    cout << endl;

    vsDepth.setMirroringEnabled(false);
    if ( STATUS_OK != vsDepth.start() )
    {
        cout << "ERROR: Cannot start depth stream on device" << endl << endl;
        return 1;
    }

    if ( STATUS_OK != vsColor.create( devDevice, SENSOR_COLOR ) ) {
        cout << "ERROR: Cannot create color stream on device" << endl << endl;
        return 1;
    }

    vsColor.setMirroringEnabled(false);
    if ( STATUS_OK != vsColor.start() )
    {
        cout << "ERROR: Cannot start color stream on device" << endl << endl;
        return 1;
    }

    status = vsDepth.getProperty<float>(ONI_STREAM_PROPERTY_HORIZONTAL_FOV, &hfov);
    status = vsDepth.getProperty<float>(ONI_STREAM_PROPERTY_VERTICAL_FOV, &vfov);

    viz::Camera tofcam(Vec2f(hfov, vfov), Size(mode.getResolutionX(), mode.getResolutionY()));

    /*
    /* Transformation: from global frame to camera frame
     */
    /// Let's assume camera has the following properties
    Vec3f cam_pos(0.0f,0.0f,0.0f), cam_focal_point(0.0f,0.0f,-1.0f), cam_y_dir(0.0f,-1.0f,0.0f);

    /// We can get the pose of the cam using makeCameraPose
    Affine3f cam_pose = viz::makeCameraPose(cam_pos, cam_focal_point, cam_y_dir);

    /// We can get the transformation matrix from camera coordinate system to global using
    /// - makeTransformToGlobal. We need the axes of the camera
    Affine3f transform = viz::makeTransformToGlobal(Vec3f(1.0f,0.0f,0.0f), Vec3f(0.0f,1.0f,0.0f), Vec3f(0.0f,0.0f,-1.0f), cam_pos);

    /// Pose of the widget in camera frame
    Affine3f cloud_pose = Affine3f().translate(Vec3f(0.0f,0.0f,0.0f));
    /// Pose of the widget in global frame
    Affine3f cloud_pose_global = transform * cloud_pose;

    /// Visualize camera coordinate frame
    viz::WCameraPosition cpw(200.0); // Coordinate axes: from camera-view-point
    viz::WCameraPosition cpw_frustum(tofcam.getFov(), 200.0); // Camera frustum
    myWindow.showWidget("CPW", cpw, cam_pose);
    myWindow.showWidget("CPW_FRUSTUM", cpw_frustum, cam_pose);

    VideoFrameRef dFrame;
    VideoFrameRef cFrame;

    Mat mPointCloud;
    Mat imgDepth, imgColor;

    do {
        if ( vsDepth.isValid() ) {
            if ( STATUS_OK == vsDepth.readFrame( &dFrame) ) {
                imgDepth = Mat( dFrame.getHeight(), dFrame.getWidth(), CV_16UC1, (void*)dFrame.getData() );
            }
        }
        if ( vsColor.isValid() ) {
            if ( STATUS_OK == vsColor.readFrame( &cFrame) ) {
                Mat imgRGBColor( cFrame.getHeight(), cFrame.getWidth(), CV_8UC3, (void*)cFrame.getData() );
                cvtColor( imgRGBColor, imgColor, CV_RGB2BGR );
            }
        }

        //Process Point Cloud
        if( !imgDepth.empty() && !imgColor.empty() )
        {
            mPointCloud = niComputeCloud( imgDepth, vsDepth );
            viz::WCloud pointCloud( mPointCloud, imgColor );
            myWindow.showWidget( "Point Cloud", pointCloud, cloud_pose_global );
            myWindow.showWidget( "Watermark", cv::viz::WText( "LIPS Corp Copyright 2018",
                                                            Point( dFrame.getWidth() / 32.0, dFrame.getHeight() / 24.0 ),
                                                            dFrame.getWidth() *  15.0 / 640.0, FONT_HERSHEY_SIMPLEX ) );
            myWindow.spinOnce(1, true); //pause 1ms to listen mouse events, set true to re-draw
        }
        //
        //In Viz, press e/E to terminate the viewer
        //
    } while (!myWindow.wasStopped());

    myWindow.removeWidget( "Point Cloud" );
    myWindow.removeWidget( "Watermark" );

    vsDepth.destroy();
    vsColor.destroy();

    devDevice.close();
    OpenNI::shutdown();

    return 0;
}
