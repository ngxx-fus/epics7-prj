#ifndef __ULTRASONIC_SENSORS_H__
#define __ULTRASONIC_SENSORS_H__

#include "Arduino.h"

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
#ifndef __us_wait
    #define __us_wait(MICRO_SEC) delayMicroseconds(MICRO_SEC)
#endif
#ifndef __ms_wait
    #define __ms_wait(MILI_SEC) delay(MILI_SEC)
#endif

/// number of ultrasonic sensors
const uint8_t US_NUM = 1;
/// list of trigger pin
const uint8_t US_TRIGGER_PIN[US_NUM] = {33};
/// list of echo pin
const uint8_t US_ECHO_PIN[US_NUM] = {32};
/// list of result of US sensors
float DISTANCE[5];

/// setup echo/trigger pin for each us
void __init_ultrasonic_sensor(){
    rept(uint8_t, i, 0, US_NUM){
        pinMode(US_TRIGGER_PIN[i], OUTPUT);
        pinMode(US_ECHO_PIN[i], INPUT_PULLDOWN);
    }
}

float get_distance(uint8_t id){
    /// send mono-pulse (width=10ns) to trigger pin
    __set_high(US_TRIGGER_PIN[id]);
    __us_wait(20);
    __set_high(US_TRIGGER_PIN[id]);
    /// wait for response from echo pin
    pulseIn(US_ECHO_PIN[id], HIGH, 1);

}

#endif