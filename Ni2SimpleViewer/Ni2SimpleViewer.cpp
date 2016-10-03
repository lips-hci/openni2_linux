#include <OpenNI.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define IMG_WIDTH 640
#define IMG_HEIGHT 480
#define IMG_FPS 30

using namespace std;
using namespace openni;
using namespace cv;

int main( int argc, char* argv[] )
{
    if ( STATUS_OK != OpenNI::initialize() ) {
        cout << "After initialization: " << OpenNI::getExtendedError() << endl;
        return 1;
    }

    Device devDevice;
    if ( STATUS_OK != devDevice.open( ANY_DEVICE) ) {
        cout << "Cannot open device: " << OpenNI::getExtendedError() << endl;
        return 1;
    }

    VideoMode mode;
    mode.setResolution( IMG_WIDTH, IMG_HEIGHT );
    mode.setFps( IMG_FPS );

    VideoStream vsDepth;
    if ( STATUS_OK != vsDepth.create( devDevice, SENSOR_DEPTH ) ) {
        cout << "Cannot create depth stream on device: " << OpenNI::getExtendedError() << endl;
        return 1;
    } else {
        mode.setPixelFormat(PIXEL_FORMAT_DEPTH_1_MM);
        if ( STATUS_OK != vsDepth.setVideoMode( mode ) ) {
            cout << "Cannot set video mode: " << OpenNI::getExtendedError() << endl;
            return 1;
        }
    }

    VideoStream vsColor;
    if ( STATUS_OK != vsColor.create( devDevice, SENSOR_COLOR ) ) {
        cout << "Cannot create color stream on device: " << OpenNI::getExtendedError() << endl;
        return 1;
    } else {
        mode.setPixelFormat(PIXEL_FORMAT_RGB888);
        if ( STATUS_OK != vsColor.setVideoMode( mode ) ) {
            cout << "Cannot set color mode: " << OpenNI::getExtendedError() << endl;
            return 1;
        }
    }

    vsDepth.start();
    vsColor.start();
    VideoFrameRef depth_frame;
    VideoFrameRef color_frame;

    while (true) {
        if ( vsDepth.isValid() ) {
            if ( STATUS_OK == vsDepth.readFrame( &depth_frame) ) {
                Mat imgDepth ( depth_frame.getHeight(), depth_frame.getWidth(), CV_16UC1, (void*)depth_frame.getData() );
                Mat img8bitDepth;
                imgDepth.convertTo( img8bitDepth, CV_8U, 255.0 / 5000 );
                imshow( "Depth view", img8bitDepth );
            }
        }
        if ( vsColor.isValid() ) {
            if ( STATUS_OK == vsColor.readFrame( &color_frame) ) {
                Mat imgColor( color_frame.getHeight(), color_frame.getWidth(), CV_8UC3, (void*)color_frame.getData() );
                Mat imgBGRColor;
                cvtColor( imgColor, imgBGRColor, CV_RGB2BGR );
                imshow( "Color view", imgBGRColor );
            }
        }
        waitKey(1);
    }
    vsDepth.destroy();
    vsColor.destroy();
 
    devDevice.close();
    OpenNI::shutdown();

    return 0;
}

