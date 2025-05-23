#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class Ultrasonic {
private:
    int trigPin;
    int echoPin;

public:
    Ultrasonic(int trig, int echo);
    float distanceCM();
};

#endif
