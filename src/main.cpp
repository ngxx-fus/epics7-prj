#include "main.hpp"

void setup(){
    
}

void loop(){
    uint8_t c_max = 2;
    while(0x1){
        delay(50);
        float d =  ultrasonic_sensor_0.measure();
        c = (c%c_max)+1;
        d_sum = (c < 2)?d:(d_sum+d);
        d_delta = (c < 2)?0:(d_delta+abs((d_sum/c)-d));
        if(c<c_max) continue;
        #if defined(LOGGER) && LOG == true
            LOGGER(
                "Count: ", c, 
                "\t\td_avg: ", d_sum/c, " cm"
                "\t\td_delta: ", (d_delta*100/d_sum), " cm"
            );
        #endif
    }
}
