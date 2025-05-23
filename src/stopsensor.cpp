#include <iostream>
#include <wiringPi.h>
#include "libraries/MPU6050.h"
#include "libraries/Ultrasonic.h"

int main() {
    wiringPiSetupGpio(); // Use BCM GPIO numbers instead

    pinMode(12, OUTPUT); // Main motor ENA
    pinMode(16, OUTPUT);
    pinMode(21, OUTPUT); // Main motor IN2 (Forward)
    pinMode(20, OUTPUT); // Main motor IN1 (Backward)




    while (true) {
        digitalWrite(16, LOW); // 50% duty cycle
        digitalWrite(5, LOW); // LED on
        digitalWrite(13, LOW); // LED on
        digitalWrite(12, LOW); // LED on
        digitalWrite(21, LOW); // LED on
        digitalWrite(20, LOW); // LED 
    }

    return 0;
}