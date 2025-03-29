#ifndef __SERIAL_LOG_HPP__
#define __SERIAL_LOG_HPP__

#include "Arduino.h"

#ifndef MONITOR_SPEED
    #define MONITOR_SPEED 115200
#endif
#ifndef HW_SERIAL_OBJ
    #define HW_SERIAL_OBJ Serial
#endif
#ifndef INIT_MESSAGE
    #define INIT_MESSAGE ">>> HELLO >>>"
#endif
class SerialLogger{
    private:
        uint32_t monitor_speed = MONITOR_SPEED;
        String init_msg = INIT_MESSAGE;
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

        void raw_write_byte_arr(uint8_t* arr, size_t len){
            Serial.write(arr, len);
        }

        template<class Tmsg>
        void raw_write(Tmsg the_msg){
            HW_SERIAL_OBJ.write(the_msg);
        }

        template<class Tmsg, class... Tmsgs>
        void raw_write(Tmsg msg, Tmsgs... msgs){
            HW_SERIAL_OBJ.write(msg);
            write(msgs...);
        }

        template<class Tmsg>
        void write(Tmsg the_msg){
            HW_SERIAL_OBJ.println(String(the_msg));
        }

        template<class Tmsg, class... Tmsgs>
        void write(Tmsg msg, Tmsgs... msgs){
            HW_SERIAL_OBJ.print(String(msg));
            write(msgs...);
        }

        template<class... Tmsgs>
        void log(Tmsgs... msgs){
            write('[', millis(), "] ", msgs...);
        }

        template<class... Tmsgs>
        void info(Tmsgs... msgs){
            write('[', millis(), "] Info: ", msgs...);
        }

        bool msg_comming(){
            return HW_SERIAL_OBJ.available();
        }

        void flush(){
            HW_SERIAL_OBJ.flush();
        }

        String read_msg(){
            String msg = "";
            while(HW_SERIAL_OBJ.available()){
                msg += (char)HW_SERIAL_OBJ.read();
                delay(1);
            }
            return msg;
        }

        ~SerialLogger(){
            HW_SERIAL_OBJ.end();
        }
};
#endif