#ifndef __MULTI_ULTRASONIC_SENSOR_H__
#define __MULTI_ULTRASONIC_SENSOR_H__

#include "Arduino.h"

#if !defined(LOG)
    #define LOG true
#endif
#if !defined(LOGGER)  && LOG == true
    #ifndef __SERIAL_LOG_HPP__
        #include "serial_com.hpp"
        SerialLogger logger;
    #endif
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


class MultiUltrasonicSensor{
    private:
        uint8_t     __pin_trigger;
        uint8_t*    __pin_echo;
        uint8_t     __num;
        bool        initialized;

        uint32_t    __last_fire_t;
        
    protected:
        
        uint32_t duration(uint32_t stop_t, uint32_t start_t){
            return stop_t-start_t;
        }

        void set_fire(){
            __last_fire_t = micros();
            digitalWrite(__pin_trigger, LOW); delayMicroseconds(5);
            digitalWrite(__pin_trigger, HIGH); delayMicroseconds(10);
            digitalWrite(__pin_trigger, LOW); delayMicroseconds(5);
        }

        uint32_t get_echo_pulse_width(uint8_t id){
            return pulseIn(__pin_echo[id], HIGH, 100000UL);
        }

    public:
        MultiUltrasonicSensor(uint8_t trigger_pin, uint8_t* const echo_pins, uint8_t num){
            if( num < 1 ) return;
            /// update number of sensors
            __num = num;
            /// new echo list via `new`
            __pin_echo = new uint8_t[__num];
            /// copy echo pins
            for(uint8_t i = 0; i < __num; ++i){
                __pin_echo[i] = echo_pins[i];
            }
            /// copy trigger pin
            __pin_trigger = trigger_pin;
            /// mark as un-initialized
            initialized = false;
        }

        bool ready(){
            return initialized;
        }

        void begin(){
            /// setup trigger pin (common pin)
            pinMode(__pin_trigger, OUTPUT);
            /// setup all echo pins
            for(uint8_t i = 0; i < __num; ++i)
                pinMode(__pin_echo[i], INPUT_PULLUP);
            /// set ready
            initialized = true;
        }

        float measure(uint8_t dev_id){
            set_fire();
            return (34000 * get_echo_pulse_width(dev_id))/ 2000000UL;
        }

        void end(){
            pinMode(__pin_trigger, INPUT);
            for(uint8_t i = 0; i < __num; ++i)
                pinMode(__pin_echo[i], INPUT);
            initialized = false;
        }

        ~MultiUltrasonicSensor(){
            delete[] __pin_echo;
        }
};

uint8_t echo_pin_list[6] = {2, 3, 4, 5, 6, 7};
MultiUltrasonicSensor sensor((uint8_t) 14, (uint8_t*) echo_pin_list, (uint8_t) 6);

#endif