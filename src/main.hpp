#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"

/// ---------------------------------------------------------------------- ///

#include "serial_com.hpp"

#define LOG true

/// ---------------------------------------------------------------------- ///

#include "multi-ultrasonic_sensor.hpp"

enum sensors_enum{FAR_LEFT=0, LEFT, CENTER, RIGHT, FAR_RIGHT, UP};
uint8_t echo_pin_list[6] = {2, 3, 4, 5, 6, 7};
MultiUltrasonicSensor sensors((uint8_t) 14, (uint8_t*) echo_pin_list, (uint8_t) 6);

/// ---------------------------------------------------------------------- ///

#if !defined(LOG)
    #define LOG false
#endif
#if !defined(LOGGER) && LOG == true
    #include "serial_com.hpp"
    SerialLogger logger(115200);
    #define  LOGGER(...) logger.log(__VA_ARGS__)
#endif

/// ---------------------------------------------------------------------- ///

#ifndef rept
    #define rept(type, i, start, stop) for(type i = (start); i < (stop); ++i)
#endif
#ifndef revt
    #define revt(type, i, start, stop) for(type i = (start); i > (stop); --i)
#endif

#ifndef __set_high
    #define __set_high(PIN) digitalWrite(PIN, HIGH)
#endif
#ifndef __set_low
    #define __set_low(PIN) digitalWrite(PIN, LOW)
#endif

#ifndef __ms_wait
    #define __ms_wait(MILI_SEC) delay(MILI_SEC)
#endif

/// ---------------------------------------------------------------------- ///

/*
Command-Frame:  [xxxxxyyy]
x is the mask for sensor measurement result querry. 
MSB-bit is far-left. y is the command
YYY
---
111 : READ ALL (don't care X)
001 : READ SELECTED (don't care {x:X|where x=0}), 
return data of selected sensors from MSB-bit (far-left).
010 : READ SELECTED with milis()

NOTE: To store a measure result sensor, 2 bytes is being used!
for each result.

RETURN FRAME:
SELECTED-SENSOR-1st  SELECTED-SENSOR-2nd      SELECTED-SENSOR-final
[XXXXXXXX XXXXXXXX]  [XXXXXXXX XXXXXXXX]  ... [XXXXXXXX XXXXXXXX]

*/

enum command_sensor_mask_enum{
    SENSOR_FAR_LEFT=0x80,       /// 1000_0000
    SENSOR_LEFT=0x40,           /// 0100_0000
    SENSOR_CENTER=0x20,         /// 0010_0000
    SENSOR_RIGHT=0x10,          /// 0001_0000
    SENSOR_FAR_RIGHT=0x08,       /// 0000_1000
    READ_ALL=0x7,
    READ_SELECTED=0x1
};

/// ---------------------------------------------------------------------- ///
String received_msg = "";

void command_processing(uint8_t command_frame){
    if((command_frame&0x7) == READ_ALL){
        // logger.write("Encode->READ_ALL");
        for(uint8_t i = 0; i < sensors.num(); ++i){
            uint16_t d_i = sensors.measure(i);
            logger.write(d_i);
            delay(50);
        }
        return;
    }
    // logger.write("Command not found!");
}

#endif