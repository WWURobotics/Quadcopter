#include "mbed.h"
#include "UM6LT/UM6LT.h"
#include "assert.h"
#include <cmath>

using namespace std;

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif // M_PI

Serial pc(USBTX, USBRX);
DigitalOut select(p8);
struct xy{

     int16_t y;
     int16_t x;
};

template <typename T>
T readRegister(int reg, SPI &sensor ){
    assert(sizeof(T) <= 4);
    select=0;
    sensor.write(0x00);
    sensor.write(reg);
    const int byte_count = sizeof(T);
    union
    {
        char value_out[byte_count];
        T retval;
    };
    for(int i=0;i<4;i++){
        if(i<byte_count)
            value_out[byte_count-i-1/*for little endian*/] = sensor.write(0);
        else
            sensor.write(0);
    }
    select=1;
    wait(0.001);
    return retval;
}

template <typename T>
void writeRegister(int reg, SPI &sensor, T value ){
    assert(sizeof(T) == 4);
    select=0;
    sensor.write(0x01);
    sensor.write(reg);
    const int byte_count = sizeof(T);
    union
    {
        char bytes[byte_count];
        T value;
    } u;
    u.value = value;
    for(int i=0;i<4;i++){
        if(i<byte_count)
            sensor.write(u.bytes[byte_count-i-1/*for little endian*/]);
        else
            sensor.write(0);
    }
    select=1;
    wait(0.001);
}

float frac(float t)
{
    return t - floor(t);
}

// convert from 16 bit int to radians : 0.00019174710761185303

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
    //sensor.autoSetAccelRef();
    //static int dataToTransmit[9] = {1/*wantCov*/, 1/*wantEulerAngles*/, 1/*wantQuat*/, 1/*wantProcMag*/, 1/*wantProcAccel*/, 1/*wantProcGyro*/, 0/*wantRawMag*/, 0/*wantRawAccel*/, 0/*wantRawGyro*/};
   //sensor.setCommParams(200, 115200, dataToTransmit, 1);
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
        phi_out = 0.5 - cos(phi / 360 * 2 * M_PI) * 0.5;
        psi_out = 0.5 - cos(psi / 360 * 2 * M_PI) * 0.5;
        theta_out = 0.5 - cos(theta / 360 * 2 * M_PI) * 0.5;
        if(++count >= 100)
        {
            count = 0;

            pc.printf("phi: %f theta: %f psi: %f pI: %i tI: %i pI: %i\r\n",phi,theta,psi,phi_theta.x,phi_theta.y,psi_i);

        }
        wait(0.01);
    }
}
