//
// Ni2ImuReader.cpp
//
// This example demonstrates how to read Inertial measurement unit (IMU: accelerometer and gyroscope)
// sensor data by OpenNI2 API.
//
#include <OpenNI.h>
#include <iostream>
#include <iomanip>

#define LIPS_STREAM_PROPERTY_IMUDATA (204)

using namespace std;
using namespace openni;

int main( int argc, char* argv[] )
{
    int total_loops = 1000;
    int sleep_ms = 100;

    if ( argc != 3 )
    {
        cout << "Usage: Ni2ImuReader [total loops] [sleep ms]" << endl;
        cout << "e.g. Ni2ImuReader 1000 100" << endl;
        cout << "read IMU 1000 times and take 100ms sleep between each read" << endl;
        exit(0);
    }
    else
    {
        total_loops = atoi(argv[1]);
        sleep_ms = atoi(argv[2]);
    }

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

    vsDepth.start();

    int loops = 0;
    while ( ++loops <= total_loops )
    {
        float IMUdata[6] = { 0 };
        int size = sizeof( IMUdata );

        if ( vsDepth.isValid() )
        {
            cout << "[" << loops << "] ";
            if( STATUS_OK == vsDepth.getProperty( LIPS_STREAM_PROPERTY_IMUDATA, IMUdata, &size ) )
            {
                cout << "Gyro (X,Y,Z) = (";
                cout << IMUdata[0] << ", " << IMUdata[1] << ", " << IMUdata[2] << "),\t";
                cout << "Accel (X,Y,Z) = (";
                cout << IMUdata[3] << ", " << IMUdata[4] << ", " << IMUdata[5] << ")" << endl;
            }
            else
            {
                cout << "Fail to read IMU data or unsupported!" << endl;
            }
        }

        usleep( sleep_ms*1000 );
    }

    vsDepth.destroy();
    devDevice.close();
    OpenNI::shutdown();

    return 0;
}
