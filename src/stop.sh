g++ -o stopsensor stopsensor.cpp libraries/MPU6050.cpp libraries/Ultrasonic.cpp -I./libraries -lwiringPi
./stopsensor
rm stopsensor