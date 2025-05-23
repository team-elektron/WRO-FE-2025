#include <cstdint>
#ifndef MPU6050_H
#define MPU6050_H

class MPU6050 {
public:
    MPU6050();
    bool begin();             // Initialize sensor
    void update();            // Read gyro and update angle
    float angle();            // Get current yaw angle
    void resetAngle();        // Reset yaw to 0

private:
    int file;
    float yaw;
    float gyro_scale;
    int16_t read_word_2c(char* data, int idx);
    long lastMicros;
};

#endif
