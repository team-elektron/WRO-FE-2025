#include <iostream>
#include <unistd.h>
#include "MPU6050.h"
#include "Ultrasonic.h"
#include "wiringPi.h"
#include <softPwm.h>

int main() {
    wiringPiSetupGpio();  // Enables BCM numbering

    pinMode(12, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(26, INPUT);
    pullUpDnControl(26, PUD_UP);      // Enable internal pull-up resistor

    int gomode = 0;

    int ENAPin = 12; // BCM 12
    softPwmCreate(12, 0, 100); // Pin 12, initial 0, range 0–100
    int ENBPin = 16; // BCM 16
    softPwmCreate(16, 0, 100); // Pin 16, initial 0, range 0–100


    std::cout << "Starting sensor loop" << std::endl;

    MPU6050 mpu6050;
    mpu6050.begin();

    Ultrasonic sensor1(23, 24);  // Trig, Echo
    Ultrasonic sensor2(27, 22);
    Ultrasonic sensor3(17, 18);

    while (true) {
        mpu6050.update();
        float angle = mpu6050.angle();
        float dist1 = sensor1.distanceCM();
        float dist2 = sensor2.distanceCM();
        float dist3 = sensor3.distanceCM();

        std::cout << "Angle: " << angle
                  << " | Distances: "
                  << dist1 << "cm, "
                  << dist2 << "cm, "
                  << dist3 << "cm"
                  << std::endl;


        if (dist1 >= 100 && gomode == 0) {
            std::cout << "cmar" << std::endl;
            softPwmWrite(ENAPin, 25); // 50% duty cycle
            digitalWrite(21, HIGH); 
            digitalWrite(20, LOW); 

            if (dist2 <= 30) {
                digitalWrite(19, HIGH);
                softPwmWrite(16, 35);
                digitalWrite(5, HIGH);
                digitalWrite(13, LOW);
            } else {
                digitalWrite(19, LOW);
                softPwmWrite(16, 35);
                digitalWrite(5, LOW);
                digitalWrite(13, HIGH);
            }
        } else {
            if (gomode == 0) {
                softPwmWrite(16, 0);
                softPwmWrite(12, 50);
                digitalWrite(21, LOW);  
                digitalWrite(20, HIGH);  
                delay(100);
                softPwmWrite(12, 0); // 50% duty cycle
                digitalWrite(21, LOW);  
                digitalWrite(20, LOW);  
                gomode = 1;
                mpu6050.resetAngle();
            } else {}
            //usleep(1000);
            std::cout << gomode << std::endl;
                if (angle >= -90 && gomode == 1) {
                    softPwmWrite(16, 35);
                    digitalWrite(5, HIGH);
                    digitalWrite(13, LOW);
                    usleep(10000);
                    softPwmWrite(12, 29); // 50% duty cycle
                    digitalWrite(21, HIGH);  
                    digitalWrite(20, LOW);  
                } else {
                    softPwmWrite(16, 0);
                    softPwmWrite(12, 100); // 50% duty cycle
                    digitalWrite(21, LOW);  
                    digitalWrite(20, LOW);  
                    usleep(10000);
                    softPwmWrite(12, 0); // 50% duty cycle
                    digitalWrite(21, LOW);  
                    digitalWrite(20, LOW);  
                    //break;
                    gomode = 0;
                }
            
        }
        //std::cout << gomode << std::endl;

        usleep(50000);  // 50ms delay
        
    }

    return 0;
}
