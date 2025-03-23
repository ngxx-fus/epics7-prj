// #include "main.hpp"
#include "Arduino.h"
#include "serial_com.hpp"

void setup(){
    logger.begin();
    HW_SERIAL_OBJ.println("????");
    logger.log("Hello!");
    logger.log("Hello!");
}

void loop(){
    logger.log("Hello!");
    HW_SERIAL_OBJ.println("????");
}
