#include "Ultrasonic.h"
#include <wiringPi.h>
#include <unistd.h>  // for usleep
#include <sys/time.h>  // for gettimeofday

Ultrasonic::Ultrasonic(int trig, int echo) {
    trigPin = trig;
    echoPin = echo;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
    delay(50);  // sensor settle
}

float Ultrasonic::distanceCM() {
    // Send 10us pulse
    digitalWrite(trigPin, LOW);
    usleep(2);
    digitalWrite(trigPin, HIGH);
    usleep(10);
    digitalWrite(trigPin, LOW);

    // Wait for echo to go HIGH
    unsigned int timeout = 30000;
    while (digitalRead(echoPin) == LOW && timeout--) usleep(1);
    if (timeout == 0) return -1.0;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    timeout = 30000;
    while (digitalRead(echoPin) == HIGH && timeout--) usleep(1);
    if (timeout == 0) return -1.0;

    gettimeofday(&end, NULL);

    // Time difference in microseconds
    long micros = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
    float distance = micros * 0.0343 / 2;  // speed of sound: 343 m/s

    return distance;
}
