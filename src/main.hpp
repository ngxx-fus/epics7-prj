#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"

/// ---------------------------------------------------------------------- ///

#define INIT_MESSAGE ""
#include "serial_com.hpp"
SerialLogger logger;

#define LOG true

/// ---------------------------------------------------------------------- ///

#include "multi-ultrasonic_sensor.hpp"

enum sensors_enum{FAR_LEFT=0, LEFT, CENTER, RIGHT, FAR_RIGHT, UP};
uint8_t echo_pin_list[6] = {A3, 3, 4, 5, 6, 7};
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

#ifndef __min
    #define __min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef __max
    #define __max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef __abs
    #define __abs(a) ((a)<0?-(a):(a))
#endif


/// ---------------------------------------------------------------------- ///
#include "Wire.h"
#include "LSM303.h"


LSM303 compass;
LSM303::vector<int16_t> acc = {0, 0, 0}, old_acc = {0, 0, 0}, delta = {0, 0, 0};

void calc_changed_acc(LSM303::vector<int16_t> &result){
    result.x = acc.x - old_acc.x;
    result.y = acc.y - old_acc.y;
    result.z = acc.z - old_acc.z;
}

void LSM303_COPY_VECTOR(LSM303::vector<int16_t> const& from, LSM303::vector<int16_t> &to){
    to.x = from.x;
    to.y = from.y;
    to.z = from.z;
}

int16_t LSM303_MIN_VECTOR(LSM303::vector<int16_t> const& v){
    return __min(v.x, __min(v.y, v.z));
}

#define MpSs (9.8f/16384.0f)  /// MeterPerSecondSquared
#define acc_x_norm_value 3.5685 
#define acc_y_norm_value 6.051
#define acc_z_norm_value 7.6275

/// ---------------------------------------------------------------------- ///
#define __SoFr  0xAFFF
#define __EoFr  0x5FFF
uint16_t data_frame[] = {
    __SoFr,
    0, 0, 0, 0, 0, 0,
    0, 0, 0,
    __EoFr
};


String received_msg = "";

void get_data_frame(){
    rept(uint8_t, i, 0, 6){
        data_frame[i+1] = sensors.measure(i);
        delay(25);
    }
    compass.read();
    auto x = (double)compass.a.x;
    auto y = (double)compass.a.y;
    auto z = (double)compass.a.z;
    x = 100 * ( x*MpSs);
    y = 100 * (y*MpSs);
    z = 100 * (z*MpSs);
    data_frame[7] = x;
    data_frame[8] = y;
    data_frame[9] = z;
}

void send_data_frame(){
    for(auto const &data:data_frame){
        logger.raw_write_byte_arr((uint8_t*)&data, sizeof(data));
    }
}


/// ---------------------------------------------------------------------- ///
#ifndef __set_to
    #define __set_to(x, val) (((x)<(val))?(val):(x))
#endif

#ifndef __bounded_incr
    #define __bounded_incr(x, val, bounded) ((x)+(val) < (bounded) ? (x)+(val) : (val))
#endif

#define __in_range(l, x, r) ((l) <= (x) && (x) <= (r))
#define thres 50

uint8_t left_val, right_val;

void init_speaker(){
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    left_val = right_val = 0;
}


void warning(){
    left_val = 0; right_val = 0;

    if( __in_range(5, data_frame[3], thres) 
        || __in_range(5, data_frame[6], thres) ){
        left_val    =   __bounded_incr(left_val, 1, 1);
        right_val   =   __bounded_incr(right_val, 1, 1);
    }

    if (__in_range(5, data_frame[1], thres) ){
        left_val = __bounded_incr(left_val, 2, 3);
    }

    if (__in_range(5, data_frame[2], thres) ){
        left_val = __bounded_incr(left_val, 1, 2);
    }

    if (__in_range(5, data_frame[4], thres) ){
        right_val = __bounded_incr(right_val, 1, 2);
    }

    if (__in_range(5, data_frame[5], thres) ){
        right_val = __bounded_incr(right_val, 2, 3);
    }

    analogWrite(10, left_val);
    analogWrite(11, right_val);
    return;
    calc_changed_acc(delta);
    LSM303_COPY_VECTOR(delta, old_acc);
    if(__abs(LSM303_MIN_VECTOR(delta)) > 1){
        analogWrite(10, left_val);
        analogWrite(11, right_val);
    }else{
        analogWrite(10, 0);
        analogWrite(11, 0);
    }
}


#endif