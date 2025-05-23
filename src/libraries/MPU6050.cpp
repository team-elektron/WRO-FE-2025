#include "MPU6050.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <chrono>

#define MPU_ADDR 0x68

MPU6050::MPU6050() : yaw(0), gyro_scale(131.0), lastMicros(0) {}

bool MPU6050::begin() {
    const char *bus = "/dev/i2c-1";
    if ((file = open(bus, O_RDWR)) < 0 || ioctl(file, I2C_SLAVE, MPU_ADDR) < 0) {
        std::cerr << "MPU6050: Failed to connect to I2C\n";
        return false;
    }

    // Wake up MPU6050
    char wake[2] = {0x6B, 0};
    write(file, wake, 2);
    usleep(1000);

    lastMicros = std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::steady_clock::now().time_since_epoch()
                 ).count();

    return true;
}

int16_t MPU6050::read_word_2c(char* data, int idx) {
    return (data[idx] << 8) | data[idx+1];
}

void MPU6050::update() {
    char reg = 0x43;  // GYRO_XOUT_H (start of gyro data)
    write(file, &reg, 1);
    char data[6];
    read(file, data, 6);

    int16_t gz_raw = read_word_2c(data, 4);  // Z-axis gyro

    auto nowMicros = std::chrono::duration_cast<std::chrono::microseconds>(
                         std::chrono::steady_clock::now().time_since_epoch()
                     ).count();
    float dt = (nowMicros - lastMicros) / 1e6f;  // in seconds
    lastMicros = nowMicros;

    float gz = gz_raw / gyro_scale;  // deg/sec
    yaw += gz * dt;

    // Normalize yaw to -180 to 180
    if (yaw > 180) yaw -= 360;
    else if (yaw < -180) yaw += 360;
}

float MPU6050::angle() {
    return yaw;
}

void MPU6050::resetAngle() {
    yaw = 0;
}
