#include "um6lt.h"
#include "mbed.h"
#include "gtimer.h"
#include "mbedio.h"
#include <cstdint>

namespace quadcopter
{

namespace
{
// UM6 Configuration Registers

const int um6ltCOMMUNICATION = 0x00;
const int um6ltMISC_CONFIG = 0x01;
const int um6ltMAG_REF_X = 0x02;
const int um6ltMAG_REF_Y = 0x03;
const int um6ltMAG_REF_Z = 0x04;
const int um6ltACCEL_REF_X = 0x05;
const int um6ltACCEL_REF_Y = 0x06;
const int um6ltACCEL_REF_Z = 0x07;
const int um6ltEKF_MAG_VARIANCE = 0x08;
const int um6ltEKF_ACCEL_VARIANCE = 0x09;
const int um6ltEKF_PROCESS_VARIANCE = 0x0A;
const int um6ltGYRO_BIAS_XY = 0x0B;
const int um6ltGYRO_BIAS_Z = 0x0C;
const int um6ltACCEL_BIAS_XY = 0x0D;
const int um6ltACCEL_BIAS_Z = 0x0E;
const int um6ltMAG_BIAS_XY = 0x0F;
const int um6ltMAG_BIAS_Z = 0x10;
const int um6ltACCEL_CAL_00 = 0x11;
const int um6ltACCEL_CAL_01 = 0x12;
const int um6ltACCEL_CAL_02 = 0x13;
const int um6ltACCEL_CAL_10 = 0x14;
const int um6ltACCEL_CAL_11 = 0x15;
const int um6ltACCEL_CAL_12 = 0x16;
const int um6ltACCEL_CAL_20 = 0x17;
const int um6ltACCEL_CAL_21 = 0x18;
const int um6ltACCEL_CAL_22 = 0x19;
const int um6ltGYRO_CAL_00 = 0x1A;
const int um6ltGYRO_CAL_01 = 0x1B;
const int um6ltGYRO_CAL_02 = 0x1C;
const int um6ltGYRO_CAL_10 = 0x1D;
const int um6ltGYRO_CAL_11 = 0x1E;
const int um6ltGYRO_CAL_12 = 0x1F;
const int um6ltGYRO_CAL_20 = 0x20;
const int um6ltGYRO_CAL_21 = 0x21;
const int um6ltGYRO_CAL_22 = 0x22;
const int um6ltMAG_CAL_00 = 0x23;
const int um6ltMAG_CAL_01 = 0x24;
const int um6ltMAG_CAL_02 = 0x25;
const int um6ltMAG_CAL_10 = 0x26;
const int um6ltMAG_CAL_11 = 0x27;
const int um6ltMAG_CAL_12 = 0x28;
const int um6ltMAG_CAL_20 = 0x29;
const int um6ltMAG_CAL_21 = 0x2A;
const int um6ltMAG_CAL_22 = 0x2B;

// UM6 Data Registers

const int um6ltSTATUS  = 0x55;
const int um6ltGYRO_RAW_XY = 0x56;
const int um6ltGYRO_RAW_Z = 0x57;
const int um6ltACCEL_RAW_XY = 0x58;
const int um6ltACCEL_RAW_Z = 0x59;
const int um6ltMAG_RAW_XY = 0x5A;
const int um6ltMAG_RAW_Z = 0x5B;
const int um6ltGYRO_PROC_XY = 0x5C;
const int um6ltGYRO_PROC_Z = 0x5D;
const int um6ltACCEL_PROC_XY = 0x5E;
const int um6ltACCEL_PROC_Z = 0x5F;
const int um6ltMAG_PROC_XY = 0x60;
const int um6ltMAG_PROC_Z = 0x61;
const int um6ltEULER_PHI_THETA = 0x62;
const int um6ltEULER_PSI = 0x63;
const int um6ltQUAT_AB  = 0x64;
const int um6ltQUAT_CD  = 0x65;
const int um6ltERROR_COV_00 = 0x66;
const int um6ltERROR_COV_01 = 0x67;
const int um6ltERROR_COV_02 = 0x68;
const int um6ltERROR_COV_03 = 0x69;
const int um6ltERROR_COV_10 = 0x6A;
const int um6ltERROR_COV_11 = 0x6B;
const int um6ltERROR_COV_12 = 0x6C;
const int um6ltERROR_COV_13 = 0x6D;
const int um6ltERROR_COV_20 = 0x6E;
const int um6ltERROR_COV_21 = 0x6F;
const int um6ltERROR_COV_22 = 0x70;
const int um6ltERROR_COV_23 = 0x71;
const int um6ltERROR_COV_30 = 0x72;
const int um6ltERROR_COV_31 = 0x73;
const int um6ltERROR_COV_32 = 0x74;
const int um6ltERROR_COV_33 = 0x75;

// UM6 Command Registers

const int um6ltGET_FW_VERSION = 0xAA;
const int um6ltFLASH_COMMIT = 0xAB;
const int um6ltZERO_GYROS = 0xAC;
const int um6ltRESET_EKF = 0xAD;
const int um6ltGET_DATA = 0xAE;
const int um6ltSET_ACCEL_REF = 0xAF;
const int um6ltSET_MAG_REF = 0xB0;
const int um6ltRESET_TO_FACTORY = 0xB1;

const int um6ltBAD_CHECKSUM = 0xFD;
const int um6ltUNKNOWN_ADDRESS = 0xFE;
const int um6ltINVALID_BATCH_SIZE = 0xFF;

// UM6 scale factors

const float um6ltANGLE_FACTOR = 0.0109863;
const float um6ltACCEL_FACTOR = 0.000183105;
const float um6ltMAG_FACTOR = 0.000305176;
const float um6ltANGLE_RATE_FACTOR = 0.0610352;
const float um6ltQUATERNION_FACTOR = 0.0000335693;

template <typename T>
T readRegister(int reg, mbed::SPI &sensor, mbed::DigitalOut &select)
{
    static_assert(sizeof(T) <= 4, "sizeof(T) > 4");
    select = 0;
    sensor.write(0x00);
    sensor.write(reg);
    const int byte_count = sizeof(T);
    union
    {
        char value_out[byte_count];
        T retval;
    };

    for(int i = 0; i < 4; i++)
    {
        if(i < byte_count)
        {
            value_out[byte_count - i - 1] = sensor.write(0);    //for little endian
        }
        else
        {
            sensor.write(0);
        }
    }

    select = 1;
    wait(0.001);
    return retval;
}

template <typename T>
void writeRegister(int reg, mbed::SPI &sensor, mbed::DigitalOut &select, T value)
{
    static_assert(sizeof(T) <= 4, "sizeof(T) > 4");
    select = 0;
    sensor.write(0x01);
    sensor.write(reg);
    const int byte_count = sizeof(T);
    union
    {
        char bytes[byte_count];
        T value;
    } u;
    u.value = value;

    for(int i = 0; i < 4; i++)
    {
        if(i < byte_count)
        {
            sensor.write(u.bytes[byte_count - i - 1]);    //for little endian
        }
        else
        {
            sensor.write(0);
        }
    }

    select = 1;
    wait(0.001);
}


}

UM6LT::UM6LT(PinName select, PinName mosi, PinName miso, PinName sck)
    : spi(mosi, miso, sck), select(select)
{
    this->select.write(1);
    spi.frequency(100000);
    delay(0.001);
    writeRegister<uint32_t>(um6ltMISC_CONFIG, spi, this->select, 0xF0000000U); // um6lt datasheet p.35
    delay(0.1);
    //TODO(jacob#): check for self test failure in um6ltSTATUS
}

namespace
{
struct int16_t_x2
{
    int16_t b, a;
    int16_t_x2(int16_t a, int16_t b)
        : b(b), a(a)
    {
    }
} __attribute__((packed));
typedef int16_t_x2 int16_t_x2;
}

void UM6LT::update()
{
    //TODO(jacob#): test
    float qa, qb, qc, qd;
    auto qab = readRegister<int16_t_x2>(um6ltQUAT_AB, spi, select);
    auto qcd = readRegister<int16_t_x2>(um6ltQUAT_CD, spi, select);
    qa = um6ltQUATERNION_FACTOR * qab.a;
    qb = um6ltQUATERNION_FACTOR * qab.b;
    qc = um6ltQUATERNION_FACTOR * qcd.a;
    qd = um6ltQUATERNION_FACTOR * qcd.b;
    Vector3D acceleration;
    auto axy = readRegister<int16_t_x2>(um6ltACCEL_PROC_XY, spi, select);
    auto az = readRegister<int16_t_x2>(um6ltACCEL_PROC_Z, spi, select);
    mbedOut << "read accel : XY : " << axy.a << " " << axy.b << " : Z : " << az.a << " " << az.b << endl;
    acceleration.x = axy.a * um6ltACCEL_FACTOR;
    acceleration.y = axy.b * um6ltACCEL_FACTOR;
    acceleration.z = az.a * um6ltACCEL_FACTOR;
    handleUpdate(convertFromGsToMetersPerSecondSquared(acceleration), Matrix4x4::fromNormalizedQuaternion(qa, qb, qc, qd));
}

/*
struct xy{

     int16_t y;
     int16_t x;
};

float frac(float t)
{
    return t - floor(t);
}

int main() {
//UM6LT sensor(p9,p10);
//I2C sensor(p9, p10);
    SPI sensor(p5, p6, p7);
    PwmOut phi_out(LED1);
    PwmOut theta_out(LED2);
    PwmOut psi_out(LED3);
    phi_out.period(30.0 / 1000);
    theta_out.period(30.0 / 1000);
    psi_out.period(30.0 / 1000);


   // int roll,pitch,yaw;
    //sensor.autoSetAccelRef();*/
//static int dataToTransmit[9] = {1/*wantCov*/, 1/*wantEulerAngles*/, 1/*wantQuat*/, 1/*wantProcMag*/, 1/*wantProcAccel*/, 1/*wantProcGyro*/, 0/*wantRawMag*/, 0/*wantRawAccel*/, 0/*wantRawGyro*/};
/*//sensor.setCommParams(200, 115200, dataToTransmit, 1);
 select=1;
 wait(0.05);
 sensor.frequency(50000);

 //sensor.baud(115200);
 wait(0.05);




 int count = 0;
 while(1) {

     //sensor.getAngles(roll, pitch, yaw); // in degrees
     //value = readRegister<xy>(UM6_GYRO_PROC_XY,sensor);
     xy phi_theta = readRegister<xy>(UM6_EULER_PHI_THETA,sensor);
     int psi_i = readRegister<xy>(UM6_EULER_PSI,sensor).x;
     float phi = phi_theta.x*0.0109863;
     float theta = phi_theta.y*0.0109863;
     float psi = psi_i*0.0109863;
     phi_out = 0.5 - cos(phi / 360 * 2 * PI) * 0.5;
     psi_out = 0.5 - cos(psi / 360 * 2 * PI) * 0.5;
     theta_out = 0.5 - cos(theta / 360 * 2 * PI) * 0.5;
     if(++count >= 100)
     {
         count = 0;

         pc.printf("phi: %f theta: %f psi: %f pI: %i tI: %i pI: %i\r\n",phi,theta,psi,phi_theta.x,phi_theta.y,psi_i);

     }
     wait(0.01);
 }
}
*/
}

