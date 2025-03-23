#ifndef __ULTRASONIC_SENSOR_H__
#define __ULTRASONIC_SENSOR_H__

#include "Arduino.h"

#if !defined(LOG)
    #define LOG false
#endif
#if !defined(LOGGER)  && LOG == true
    #include "serial_com.hpp"
    SerialLogger logger(115200);
    #define  LOGGER(...) logger.log(__VA_ARGS__)
#endif

#ifndef rept
    #define rept(type, i, start, stop) for(type i = (start); i < (stop); ++i)
#endif
#ifndef revt
    #define revt(type, i, start, stop) for(type i = (start); i > (stop); --i)
#endif

#ifndef __get_state
    #define __get_state(PIN) digitalRead(PIN)
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


class UltrasonicSensor{

private:
    
    int64_t const               __measurement_timeout = 500000 /*micro-sec*/;
    float const                 __max_distance = 330.0f;

    uint8_t __pin_trigger,      __pin_echo;
    bool    __fired;

    /// this is time_stop reserved feature!
    bool is_valid_pin(uint8_t pin){
        if( pin < 1 || pin > 40 ) return false;
        return true;
    }

protected:

    void fire_trigger(){
        if(!__pin_echo || !__pin_trigger) return;
        __set_low(__pin_trigger);   delayMicroseconds(10);
        __set_high(__pin_trigger);  delayMicroseconds(10);
        __set_low(__pin_trigger);
        __fired = true; // Mark as fired
    }
public:

    UltrasonicSensor(uint8_t trigger_pin = 0, uint8_t echo_pin = 0){
        __pin_trigger = (is_valid_pin(trigger_pin))? trigger_pin : 0, 
        __pin_echo = (is_valid_pin(echo_pin))? echo_pin : 0;
        if(!__pin_echo || !__pin_trigger) return;
        pinMode(__pin_trigger, OUTPUT);
        pinMode(__pin_echo, INPUT_PULLUP);
        #if defined(LOGGER)  && LOG == true 
            LOGGER("__pin_trigger:  ", __pin_trigger);
            LOGGER("__pin_echo   :  ", __pin_echo);
        #endif
    }

    void set_pin(uint8_t trigger_pin = 0, uint8_t echo_pin = 0){
        UltrasonicSensor(trigger_pin, echo_pin);
    }

    float measure(){
        if(!__pin_echo || !__pin_trigger) return 0; /// error

        fire_trigger();
        if(__fired == false) return -1; /// error
        #if defined(LOGGER)  && LOG == true 
            LOGGER("Sent wave     >>>");
        #endif

        float duration = pulseInLong(__pin_echo, HIGH, __measurement_timeout);
        float distance = 100 * (duration / (1e6)) * 340 / 2;
        #if defined(LOGGER)  && LOG == true 
            LOGGER("Received wave <<<");
            LOGGER("Duration     :  ", duration, " us");
            LOGGER("Distance     :  ", distance, " cm");
        #endif

        return min(distance, __max_distance); /// in centimet
    }

    ~UltrasonicSensor(){
        pinMode(__pin_echo, INPUT);
        pinMode(__pin_trigger, INPUT);
        #if defined(LOGGER)  && LOG == true 
            LOGGER("__pin_trigger:  ", "INPUT");
            LOGGER("__pin_echo   :  ", "INPUT");
        #endif
    }
};


UltrasonicSensor    ultrasonic_sensor_0(21, 22);
uint8_t c = 0;
float d_sum = 0;
float d_avg = 0;
float d_delta = 0;

#endif