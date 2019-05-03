
#ifndef _APP_H
#define _APP_H

#include <Arduino.h>

#include <Version.def>

#include <Bluetooth/Bluetooth.h>
#include <Countdown/Countdown.h>
#include <Lamp/Lamp.h>

#define REFRESH_TIME 3000

class App {
    private:
        Countdown* mainTimeout;
        Bluetooth* bluetooth;
        Lamp* lamp;

    public:
        App();
        void process();
        void init();
};

#endif
