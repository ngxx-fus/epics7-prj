#ifndef __SERIAL_LOG_HPP__
#define __SERIAL_LOG_HPP__

#include "Arduino.h"

#define MONITOR_SPEED 115200
#define HW_SERIAL_OBJ Serial

class SerialLogger{
    private:
        uint32_t monitor_speed = MONITOR_SPEED;
        String init_msg = ">>> HELLO >>>";
        bool initialized;

    protected:
        void change_init_msg(String new_init_msg){
            this->init_msg = new_init_msg;
        }

    public:

        SerialLogger(uint32_t monitor_speed = MONITOR_SPEED){
            this->monitor_speed = monitor_speed;
            this->initialized = false;
        }

        bool ready(){
            return initialized;
        }
        
        void begin(uint32_t monitor_speed = MONITOR_SPEED){
            this->monitor_speed = monitor_speed;
            HW_SERIAL_OBJ.begin(this->monitor_speed);
            HW_SERIAL_OBJ.println(init_msg);
            initialized = true;
        }
        
        void end(){
            HW_SERIAL_OBJ.end();
            initialized = false;
        }

        void set_monitor_speed(uint32_t monitor_speed = MONITOR_SPEED){
            this->monitor_speed = monitor_speed;
            HW_SERIAL_OBJ.end();
            HW_SERIAL_OBJ.begin(this->monitor_speed);
            HW_SERIAL_OBJ.println(init_msg);
        }

        template<class Tmsg>
        void print(Tmsg the_msg){
            HW_SERIAL_OBJ.println(String(the_msg));
        }

        template<class Tmsg, class... Tmsgs>
        void print(Tmsg msg, Tmsgs... msgs){
            HW_SERIAL_OBJ.print(String(msg));
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
            HW_SERIAL_OBJ.end();
        }
};

SerialLogger logger;

#endif