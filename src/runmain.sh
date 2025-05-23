g++ -o main main.cpp libraries/MPU6050.cpp libraries/Ultrasonic.cpp -I./libraries -lwiringPi
./main
rm main