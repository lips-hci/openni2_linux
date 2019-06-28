//
// Ni2CameraMatrix.cpp
//
// This example demonstrates how to get camera intrinsic matrix by OpenNI2 API.
//
#include <OpenNI.h>
#include <iostream>
#include <iomanip>

#define MAX_STR_SIZE 128

enum
{
    // Camera
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_X     = 200,
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_Y     = 201,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_X  = 202,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_Y  = 203
};

using namespace std;
using namespace openni;

int main( int argc, char* argv[] )
{
    double fx, fy, cx, cy;
    char strDepBuff[MAX_STR_SIZE] = { 0 };
    char strImgBuff[MAX_STR_SIZE] = { 0 };

	if ( STATUS_OK != OpenNI::initialize() )
	{
        cout << "After initialization: " << OpenNI::getExtendedError() << endl;
        return 1;
    }

    Device devDevice;
    if ( STATUS_OK != devDevice.open( ANY_DEVICE ) )
    {
        cout << "Cannot open device: " << OpenNI::getExtendedError() << endl;
        return 1;
    }

    VideoStream vsDepth;
    if ( STATUS_OK != vsDepth.create( devDevice, SENSOR_DEPTH ) )
    {
        cout << "Cannot create depth stream on device: " << OpenNI::getExtendedError() << endl;
        return 1;
    }

    vsDepth.getProperty(LIPS_STREAM_PROPERTY_FOCAL_LENGTH_X, &fx);
    vsDepth.getProperty(LIPS_STREAM_PROPERTY_FOCAL_LENGTH_Y, &fy);
    vsDepth.getProperty(LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_X, &cx);
    vsDepth.getProperty(LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_Y, &cy);
    vsDepth.destroy();

    sprintf(strDepBuff, "fx=%f, fy=%f, cx=%f, cy=%f\n", fx, fy, cx, cy);

    VideoStream vsColor;

    if ( STATUS_OK != vsColor.create( devDevice, SENSOR_COLOR ) ) {
        cout << "Cannot create color stream on device: " << OpenNI::getExtendedError() << endl;
        //return 1;
    } else {
        vsColor.getProperty(LIPS_STREAM_PROPERTY_FOCAL_LENGTH_X, &fx);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_FOCAL_LENGTH_Y, &fy);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_X, &cx);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_Y, &cy);
        vsColor.destroy();

        sprintf(strImgBuff, "fx=%f, fy=%f, cx=%f, cy=%f\n", fx, fy, cx, cy);
    }

    cout << endl;
    cout << "=== Camera matrix ===" << endl;
    cout << "[Depth camera]" << endl;
    cout << strDepBuff << endl;
    cout << "[Image camera]" << endl;
    cout << strImgBuff << endl;

    devDevice.close();
    OpenNI::shutdown();

	return 0;
}
