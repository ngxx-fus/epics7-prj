#include "main.hpp"

void setup(){
    logger.begin();
    sensors.begin();
    Wire.begin();
    compass.init();
    compass.enableDefault();
}

void loop(){
    get_data_frame();
    send_data_frame();
    warning();
}
