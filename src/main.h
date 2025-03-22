#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"

#define __set_high(PIN) digitalWrite(PIN, HIGH)
#define __set_low(PIN) digitalWrite(PIN, LOW)
#define __wait(MILI_SEC) delay(MILI_SEC)
const uint8_t OUTPIN0 = 16;
const uint8_t OUTPIN1 = 17;

void __init_out_pins(){
    pinMode(OUTPIN0, OUTPUT);
    pinMode(OUTPIN1, OUTPUT);
    
}

#endif