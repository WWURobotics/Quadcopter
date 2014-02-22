#include "um6lt.h"

namespace quadcopter
{

// UM6 Configuration Registers

#define UM6_COMMUNICATION           0x00
#define UM6_MISC_CONFIG             0x01
#define UM6_MAG_REF_X               0x02
#define UM6_MAG_REF_Y               0x03
#define UM6_MAG_REF_Z               0x04
#define UM6_ACCEL_REF_X             0x05
#define UM6_ACCEL_REF_Y             0x06
#define UM6_ACCEL_REF_Z             0x07
#define UM6_EKF_MAG_VARIANCE        0x08
#define UM6_EKF_ACCEL_VARIANCE      0x09
#define UM6_EKF_PROCESS_VARIANCE    0x0A
#define UM6_GYRO_BIAS_XY            0x0B
#define UM6_GYRO_BIAS_Z             0x0C
#define UM6_ACCEL_BIAS_XY           0x0D
#define UM6_ACCEL_BIAS_Z            0x0E
#define UM6_MAG_BIAS_XY             0x0F
#define UM6_MAG_BIAS_Z              0x10
#define UM6_ACCEL_CAL_00            0x11
#define UM6_ACCEL_CAL_01            0x12
#define UM6_ACCEL_CAL_02            0x13
#define UM6_ACCEL_CAL_10            0x14
#define UM6_ACCEL_CAL_11            0x15
#define UM6_ACCEL_CAL_12            0x16
#define UM6_ACCEL_CAL_20            0x17
#define UM6_ACCEL_CAL_21            0x18
#define UM6_ACCEL_CAL_22            0x19
#define UM6_GYRO_CAL_00             0x1A
#define UM6_GYRO_CAL_01             0x1B
#define UM6_GYRO_CAL_02             0x1C
#define UM6_GYRO_CAL_10             0x1D
#define UM6_GYRO_CAL_11             0x1E
#define UM6_GYRO_CAL_12             0x1F
#define UM6_GYRO_CAL_20             0x20
#define UM6_GYRO_CAL_21             0x21
#define UM6_GYRO_CAL_22             0x22
#define UM6_MAG_CAL_00              0x23
#define UM6_MAG_CAL_01              0x24
#define UM6_MAG_CAL_02              0x25
#define UM6_MAG_CAL_10              0x26
#define UM6_MAG_CAL_11              0x27
#define UM6_MAG_CAL_12              0x28
#define UM6_MAG_CAL_20              0x29
#define UM6_MAG_CAL_21              0x2A
#define UM6_MAG_CAL_22              0x2B

// UM6 Data Registers

#define UM6_STATUS                  0x55
#define UM6_GYRO_RAW_XY             0x56
#define UM6_GYRO_RAW_Z              0x57
#define UM6_ACCEL_RAW_XY            0x58
#define UM6_ACCEL_RAW_Z             0x59
#define UM6_MAG_RAW_XY              0x5A
#define UM6_MAG_RAW_Z               0x5B
#define UM6_GYRO_PROC_XY            0x5C
#define UM6_GYRO_PROC_Z             0x5D
#define UM6_ACCEL_PROC_XY           0x5E
#define UM6_ACCEL_PROC_Z            0x5F
#define UM6_MAG_PROC_XY             0x60
#define UM6_MAG_PROC_Z              0x61
#define UM6_EULER_PHI_THETA         0x62
#define UM6_EULER_PSI               0x63
#define UM6_QUAT_AB                 0x64
#define UM6_QUAT_CD                 0x65
#define UM6_ERROR_COV_00            0x66
#define UM6_ERROR_COV_01            0x67
#define UM6_ERROR_COV_02            0x68
#define UM6_ERROR_COV_03            0x69
#define UM6_ERROR_COV_10            0x6A
#define UM6_ERROR_COV_11            0x6B
#define UM6_ERROR_COV_12            0x6C
#define UM6_ERROR_COV_13            0x6D
#define UM6_ERROR_COV_20            0x6E
#define UM6_ERROR_COV_21            0x6F
#define UM6_ERROR_COV_22            0x70
#define UM6_ERROR_COV_23            0x71
#define UM6_ERROR_COV_30            0x72
#define UM6_ERROR_COV_31            0x73
#define UM6_ERROR_COV_32            0x74
#define UM6_ERROR_COV_33            0x75

// UM6 Command Registers

#define UM6_GET_FW_VERSION          0xAA
#define UM6_FLASH_COMMIT            0xAB
#define UM6_ZERO_GYROS              0xAC
#define UM6_RESET_EKF               0xAD
#define UM6_GET_DATA                0xAE
#define UM6_SET_ACCEL_REF           0xAF
#define UM6_SET_MAG_REF             0xB0
#define UM6_RESET_TO_FACTORY        0xB1

#define UM6_BAD_CHECKSUM            0xFD
#define UM6_UNKNOWN_ADDRESS         0xFE
#define UM6_INVALID_BATCH_SIZE      0xFF

// UM6 scale factors

#define UM6_ANGLE_FACTOR            0.0109863
#define UM6_ACCEL_FACTOR            0.000183105
#define UM6_MAG_FACTOR              0.000305176
#define UM6_ANGLE_RATE_FACTOR       0.0610352
#define UM6_QUATERNION_FACTOR       0.0000335693

UM6LT::UM6LT(mbed::PinName select, mbed::PinName mosi, mbed::PinName miso, mbed::PinName sck)
    : spi(mosi, miso, sck), select(select)
{
    this->select.write(1);
    spi.frequency(100000);
}

void UM6LT::update()
{
#error finish implementing UM6LT::update()
}
}
