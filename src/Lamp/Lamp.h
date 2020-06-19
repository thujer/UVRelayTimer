
#ifndef _LAMP_H_
#define _LAMP_H_

#include <Arduino.h>
#include "Countdown/Countdown.h"
#include <BluetoothSerial.h>

const char PIN_RELAY = GPIO_NUM_5;

class Lamp {
    private:
        unsigned char pinRelay;
        Countdown* timeout;
        unsigned char state;
        unsigned long currentState;
        BluetoothSerial* bluetooth;

    public:
        Lamp(unsigned char pinRelay, BluetoothSerial* _bluetooth);
        void on();
        void off();
        void process();
        void stop();
        void pause();
        void resume();
        void shineDuration(unsigned int duration);
        unsigned long getTimeLeft();
        unsigned char getRunningState();

};

#endif
