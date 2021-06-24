//
// Ni2CameraMatrix.cpp
//
// This example demonstrates how to get camera intrinsic matrix by OpenNI2 API.
//
#include <OpenNI.h>
#include <iostream>
#include "LIPSNICustomProperty.h"

using namespace std;
using namespace openni;

#define MAX_STR_SIZE 1024

#ifdef WIN32
#define sprintf sprintf_s
#endif

int main( int argc, char* argv[] )
{
    double fx, fy, cx, cy;
    CameraExtrinsicMatrix extrinsicToDepth, extrinsicToColor;
    RadialDistortionCoeffs radialDistCoeffs;
    TangentialDistortionCoeffs tangentialDistCoeffs;
    char strDepBuff[MAX_STR_SIZE] = { 0 };
    char strImgBuff[MAX_STR_SIZE] = { 0 };
    char strExtrinsicDepthToDepthBuff[MAX_STR_SIZE] = { 0 };
    char strExtrinsicDepthToColorBuff[MAX_STR_SIZE] = { 0 };
    char strExtrinsicColorToDepthBuff[MAX_STR_SIZE] = { 0 };
    char strExtrinsicColorToColorBuff[MAX_STR_SIZE] = { 0 };
    char strDepthRadialDistCoeffsBuff[MAX_STR_SIZE] = { 0 };
    char strDepthTangentialDistCoeffsBuff[MAX_STR_SIZE] = { 0 };
    char strColorRadialDistCoeffsBuff[MAX_STR_SIZE] = { 0 };
    char strColorTangentialDistCoeffsBuff[MAX_STR_SIZE] = { 0 };

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
    vsDepth.getProperty(LIPS_STREAM_PROPERTY_EXTRINSIC_TO_DEPTH, &extrinsicToDepth);
    vsDepth.getProperty(LIPS_STREAM_PROPERTY_EXTRINSIC_TO_COLOR, &extrinsicToColor);
    vsDepth.getProperty(LIPS_STREAM_PROPERTY_RADIAL_DISTORTION, &radialDistCoeffs);
    vsDepth.getProperty(LIPS_STREAM_PROPERTY_TANGENTIAL_DISTORTION, &tangentialDistCoeffs);
    vsDepth.destroy();

    sprintf(strDepBuff, "fx=%f, fy=%f, cx=%f, cy=%f\n", fx, fy, cx, cy);
    sprintf(strExtrinsicDepthToDepthBuff,
            "Extrinsic from \"Depth\" To \"Depth\" :\n"
            "    Rotation Matrix:\n"
            "    %20.6f %20.6f %20.6f\n"
            "    %20.6f %20.6f %20.6f\n"
            "    %20.6f %20.6f %20.6f\n"
            "    Translation Vector:\n"
            "    %20.6f %20.6f %20.6f\n",
            extrinsicToDepth.rotation[0][0], extrinsicToDepth.rotation[0][1], extrinsicToDepth.rotation[0][2],
            extrinsicToDepth.rotation[1][0], extrinsicToDepth.rotation[1][1], extrinsicToDepth.rotation[1][2],
            extrinsicToDepth.rotation[2][0], extrinsicToDepth.rotation[2][1], extrinsicToDepth.rotation[2][2],
            extrinsicToDepth.translation[0], extrinsicToDepth.translation[1], extrinsicToDepth.translation[2]);
    sprintf(strExtrinsicDepthToColorBuff,
            "Extrinsic from \"Depth\" To \"Color\" :\n"
            "    Rotation Matrix:\n"
            "    %20.6f %20.6f %20.6f\n"
            "    %20.6f %20.6f %20.6f\n"
            "    %20.6f %20.6f %20.6f\n"
            "    Translation Vector:\n"
            "    %20.6f %20.6f %20.6f\n",
            extrinsicToColor.rotation[0][0], extrinsicToColor.rotation[0][1], extrinsicToColor.rotation[0][2],
            extrinsicToColor.rotation[1][0], extrinsicToColor.rotation[1][1], extrinsicToColor.rotation[1][2],
            extrinsicToColor.rotation[2][0], extrinsicToColor.rotation[2][1], extrinsicToColor.rotation[2][2],
            extrinsicToColor.translation[0], extrinsicToColor.translation[1], extrinsicToColor.translation[2]);
    sprintf(strDepthRadialDistCoeffsBuff,
            "k1=%f, k2=%f, k3=%f, k4=%f, k5=%f, k6=%f\n",
            radialDistCoeffs.k1, radialDistCoeffs.k2, radialDistCoeffs.k3, radialDistCoeffs.k4, radialDistCoeffs.k5, radialDistCoeffs.k6);
    sprintf(strDepthTangentialDistCoeffsBuff, "p1=%f, p2=%f\n", tangentialDistCoeffs.p1, tangentialDistCoeffs.p2);

    VideoStream vsColor;

    if ( STATUS_OK != vsColor.create( devDevice, SENSOR_COLOR ) ) {
        cout << "Cannot create color stream on device: " << OpenNI::getExtendedError() << endl;
        //return 1;
    } else {
        vsColor.getProperty(LIPS_STREAM_PROPERTY_FOCAL_LENGTH_X, &fx);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_FOCAL_LENGTH_Y, &fy);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_X, &cx);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_Y, &cy);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_EXTRINSIC_TO_DEPTH, &extrinsicToDepth);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_EXTRINSIC_TO_COLOR, &extrinsicToColor);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_RADIAL_DISTORTION, &radialDistCoeffs);
        vsColor.getProperty(LIPS_STREAM_PROPERTY_TANGENTIAL_DISTORTION, &tangentialDistCoeffs);
        vsColor.destroy();

        sprintf(strImgBuff, "fx=%f, fy=%f, cx=%f, cy=%f\n", fx, fy, cx, cy);
        sprintf(strExtrinsicColorToDepthBuff,
                "Extrinsic from \"Color\" To \"Depth\" :\n"
                "    Rotation Matrix:\n"
                "    %20.6f %20.6f %20.6f\n"
                "    %20.6f %20.6f %20.6f\n"
                "    %20.6f %20.6f %20.6f\n"
                "    Translation Vector:\n"
                "    %20.6f %20.6f %20.6f\n",
                extrinsicToDepth.rotation[0][0], extrinsicToDepth.rotation[0][1], extrinsicToDepth.rotation[0][2],
                extrinsicToDepth.rotation[1][0], extrinsicToDepth.rotation[1][1], extrinsicToDepth.rotation[1][2],
                extrinsicToDepth.rotation[2][0], extrinsicToDepth.rotation[2][1], extrinsicToDepth.rotation[2][2],
                extrinsicToDepth.translation[0], extrinsicToDepth.translation[1], extrinsicToDepth.translation[2]);
        sprintf(strExtrinsicColorToColorBuff,
                "Extrinsic from \"Color\" To \"Color\" :\n"
                "    Rotation Matrix:\n"
                "    %20.6f %20.6f %20.6f\n"
                "    %20.6f %20.6f %20.6f\n"
                "    %20.6f %20.6f %20.6f\n"
                "    Translation Vector:\n"
                "    %20.6f %20.6f %20.6f\n",
                extrinsicToColor.rotation[0][0], extrinsicToColor.rotation[0][1], extrinsicToColor.rotation[0][2],
                extrinsicToColor.rotation[1][0], extrinsicToColor.rotation[1][1], extrinsicToColor.rotation[1][2],
                extrinsicToColor.rotation[2][0], extrinsicToColor.rotation[2][1], extrinsicToColor.rotation[2][2],
                extrinsicToColor.translation[0], extrinsicToColor.translation[1], extrinsicToColor.translation[2]);
        sprintf(strColorRadialDistCoeffsBuff,
                "k1=%f, k2=%f, k3=%f, k4=%f, k5=%f, k6=%f\n",
                radialDistCoeffs.k1, radialDistCoeffs.k2, radialDistCoeffs.k3, radialDistCoeffs.k4, radialDistCoeffs.k5, radialDistCoeffs.k6);
        sprintf(strColorTangentialDistCoeffsBuff, "p1=%f, p2=%f\n", tangentialDistCoeffs.p1, tangentialDistCoeffs.p2);
    }

    cout << endl;
    cout << "=== Camera matrix ===" << endl;
    cout << "[Depth camera]" << endl;
    cout << strDepBuff << endl;
    cout << "[Image camera]" << endl;
    cout << strImgBuff << endl;
    cout << "=== Extrinsic Parameters ===" << endl;
    cout << strExtrinsicDepthToDepthBuff << endl;
    cout << strExtrinsicDepthToColorBuff << endl;
    cout << strExtrinsicColorToDepthBuff << endl;
    cout << strExtrinsicColorToColorBuff << endl;
    cout << "=== Distortion Coefficients ===" << endl;
    cout << "[Depth - Radial distortion coefficients]" << endl;
    cout << strDepthRadialDistCoeffsBuff << endl;
    cout << "[Depth - Tangential distortion coefficients]" << endl;
    cout << strDepthTangentialDistCoeffsBuff << endl;
    cout << "[Color - Radial distortion coefficients]" << endl;
    cout << strColorRadialDistCoeffsBuff << endl;
    cout << "[Color - Tangential distortion coefficients]" << endl;
    cout << strColorTangentialDistCoeffsBuff << endl;

    devDevice.close();
    OpenNI::shutdown();

	return 0;
}
