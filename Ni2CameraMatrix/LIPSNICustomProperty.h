#ifndef LIPS_NI_CUSTOME_PROPERTY
#define LIPS_NI_CUSTOME_PROPERTY

#include <cstdint>

/*
 * This header is to define LIPS customized properties for OpenNI/OpenNI2
 *
 * To create new property for your purpose, you need to define
 * Name (in string) and index number (in integer)
 *
 * NOTE: some index number are already used by NI2 and you cannot overwrite it
 *
 * Update: 2018/10/02
 */

// Define property in integer format for NI2
enum
{
    // Pixel format
    ONI_PIXEL_FORMAT_DEPTH_IR_COMPRESSED     = 150,

    // LIPS Stream properties
    // Camera matrix and IMU
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_X      = 200,
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_Y      = 201,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_X   = 202,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_Y   = 203,
    LIPS_STREAM_PROPERTY_IMUDATA             = 204, //imudata

    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_R      = 205,
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_L      = 206,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_X_R = 207,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_Y_R = 208,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_X_L = 209,
    LIPS_STREAM_PROPERTY_PRINCIPAL_POINT_Y_L = 210,
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_X_R    = 211,
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_Y_R    = 212,
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_X_L    = 213,
    LIPS_STREAM_PROPERTY_FOCAL_LENGTH_Y_L    = 214,
    LIPS_STREAM_PROPERTY_ORIGINAL_RES_X      = 215,
    LIPS_STREAM_PROPERTY_ORIGINAL_RES_Y      = 216,
    LIPS_STREAM_PROPERTY_IMU_EN              = 217, //reserved for string "imu_en"
    LIPS_DEPTH_IMU_ACCEL_OFFSET              = 218,
    LIPS_DEPTH_IMU_GYRO_OFFSET               = 219,
    LIPS_STREAM_PROPERTY_EXTRINSIC_TO_DEPTH  = 220,
    LIPS_STREAM_PROPERTY_EXTRINSIC_TO_COLOR  = 221,
    LIPS_STREAM_PROPERTY_RADIAL_DISTORTION   = 222,
    LIPS_STREAM_PROPERTY_TANGENTIAL_DISTORTION = 223,

    // Other properties
    LIPS_DEVICE_NAME                         = 300,

    // Sensor properties
    LIPS_DEPTH_SENSOR_READ_REGISTER          = 400, //lipsDepthSensorReadRegister
    LIPS_DEPTH_SENSOR_WRITE_REGISTER         = 401, //lipsDepthSensorWriteRegister
    LIPS_DEPTH_SENSOR_TEMPERATURE            = 402,
    LIPS_DEPTH_SENSOR_LOW_POWER_EN           = 403, //1=low-power mode, 0=normal mode

    // Refer to LIPS Config settings
    LIPS_CONFIG_LENS_MODE                    = 500,
};

// Define properties in string format for NI
static const char LIPS_STREAM_PROPERTY_IMUDATA_STR[] = "imudata";
static const char LIPS_DEPTH_SENSOR_READ_REGISTER_STR[] = "lipsDepthSensorReadRegister";
static const char LIPS_DEPTH_SENSOR_WRITE_REGISTER_STR[] = "lipsDepthSensorWriteRegister";
static const char LIPS_CONFIG_LENS_MODE_STR[] = "lens_mode";
static const char LIPS_DEPTH_SENSOR_TEMPERATURE_STR[] = "sensor_temp";

//IMU offset
static const char LIPS_DEPTH_IMU_ACCEL_OFFSET_STR[] = "imu_accel_offset";
static const char LIPS_DEPTH_IMU_GYRO_OFFSET_STR[] = "imu_gyro_offset";

// Pre-defined depth operation mode
static const unsigned int LIPS_CONFIG_NEAR_MODE   = 0;
static const unsigned int LIPS_CONFIG_NORMAL_MODE = 1;

typedef enum {
    STANDBY_MODE     = 0, //same as Low-Power Mode
    NORMAL_OPERATION = 1, //Active mode
    DYN_POWER_DOWN   = 2  //OPT8320 only
} DeviceFuncMode ;

typedef struct
{
    uint8_t  dev;
    uint16_t addr;
    uint8_t  MSB;
    uint8_t  LSB;
    uint32_t data;
} LIPSSensorRegRWCmd;

typedef struct CameraExtrinsicMatrix
{
    float rotation[3][3];
    float translation[3];
} CameraExtrinsicMatrix;

typedef struct RadialDistortionCoeffs
{
    double k1, k2, k3, k4, k5, k6;
} RadialDistortionCoeffs;

typedef struct TangentialDistortionCoeffs
{
    double p1, p2;
} TangentialDistortionCoeffs;

#endif //LIPS_NI_CUSTOME_PROPERTY