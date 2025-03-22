#ifndef __SERIAL_LOG_HPP__
#define __SERIAL_LOG_HPP__

#include "Arduino.h"

#define MONITOR_SPEED 115200

class SerialLogger{

private:
    uint32_t monitor_speed = MONITOR_SPEED;
    String init_msg = "\n\nHello from ESP-WROOM32!\n\n";

protected:
    void change_init_msg(String new_init_msg){
        this->init_msg = new_init_msg;
    }

public:

    SerialLogger(uint32_t monitor_speed = MONITOR_SPEED){
        this->monitor_speed = monitor_speed;
        Serial.begin(this->monitor_speed);
        Serial.println(init_msg);
    }

    void set_monitor_speed(uint32_t monitor_speed = MONITOR_SPEED){
        this->monitor_speed = monitor_speed;
        Serial.end();
        Serial.begin(this->monitor_speed);
        Serial.println(init_msg);
    }

    template<class Tmsg>
    void print(Tmsg the_msg){
        Serial.println(String(the_msg));
    }

    template<class Tmsg, class... Tmsgs>
    void print(Tmsg msg, Tmsgs... msgs){
        Serial.print(String(msg));
        print(msgs...);
    }

    template<class... Tmsgs>
    void log(Tmsgs... msgs){
        print('[', millis(), "] ", msgs...);
    }

    template<class... Tmsgs>
    void info(Tmsgs... msgs){
        print('[', millis(), "] Info: ", msgs...);
    }

    ~SerialLogger(){
        Serial.end();
    }

};

#endif