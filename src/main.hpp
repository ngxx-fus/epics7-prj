#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"

/// ---------------------------------------------------------------------- ///

#define LOG false

/// ---------------------------------------------------------------------- ///

#include "serial_com.hpp"

#include "ultrasonic_sensor.hpp"

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

#if !defined(LOGGER)
    SerialLogger        logger(115200);
    #define  LOGGER(...) logger.log(__VA_ARGS__)
#endif

UltrasonicSensor    ultrasonic_sensor_0(21, 22);

uint8_t c = 0;
float d_sum = 0;
float d_avg = 0;
float d_delta = 0;
#endif