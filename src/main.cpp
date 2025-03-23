// #include "main.hpp"
#include "Arduino.h"

#include "serial_com.hpp"
#include "multi-ultrasonic_sensor.hpp"

void setup(){
    logger.begin();
    sensor.begin();
}

String visual[11] = {
    "|         ",
    "#         ",
    "##        ",
    "###       ",
    "####      ",
    "#####     ",
    "######    ",
    "#######   ",
    "########  ",
    "######### ",
    "##########"
};

void loop(){
    for(uint8_t i = 0; i < 6; ++i){
        logger.log(visual[uint32_t(sensor.measure(i)*10/300)]);
        delay(20);
    }
    logger.log("\n\n");
    delay(100); 
