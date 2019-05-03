
#ifndef _LAMP_H_
#define _LAMP_H_

#include <Arduino.h>
#include <Countdown/Countdown.h>

const char PIN_RELAY = GPIO_NUM_5;

class Lamp {
    private:
        unsigned char pinRelay;
        Countdown* timeout;
        unsigned char state;

    public:
        Lamp(unsigned char pinRelay);
        void on();
        void off();
        void process();
        void stop();
        void shineDuration(unsigned int duration);
        unsigned long getTimeLeft();
        unsigned char getRunningState();

};

#endif
