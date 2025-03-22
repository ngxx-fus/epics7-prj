#include "main.h"

void setup(){
    __init_out_pins();
}

void loop(){
    __set_high(OUTPIN0);
    __set_low(OUTPIN1);
    __wait(500);
    __set_low(OUTPIN0);
    __set_high(OUTPIN1);
    __wait(500);
}