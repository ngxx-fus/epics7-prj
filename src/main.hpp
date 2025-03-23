#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"

/// ---------------------------------------------------------------------- ///

#include "serial_com.hpp"

// #define LOG false
// #include "ultrasonic_sensor.hpp"
#define LOG true

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

#endif