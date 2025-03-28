#include "main.hpp"

void setup(){
    logger.begin();
    sensors.begin();
}

void loop(){
    // logger.write("waiting...");
    if(logger.msg_comming()){
        received_msg = logger.read_msg();
        for(auto c:received_msg){
            // logger.write("reading... command: ", c);
            command_processing(c);
        }
    }
}
