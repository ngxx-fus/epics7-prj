#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"

#include "ultrasonic_sensors.hpp"

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

const uint8_t OUTPIN0 = 16;
const uint8_t OUTPIN1 = 17;

void __init_out_pins(){
    pinMode(OUTPIN0, OUTPUT);
    pinMode(OUTPIN1, OUTPUT);
}

#endif