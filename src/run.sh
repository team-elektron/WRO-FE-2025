g++ -o run run.cpp libraries/MPU6050.cpp libraries/Ultrasonic.cpp -I./libraries -lwiringPi
./run
rm run