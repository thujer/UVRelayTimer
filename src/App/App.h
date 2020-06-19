
#ifndef _APP_H
#define _APP_H

#include <Arduino.h>

#include <Version.def>

#include <BluetoothSerial.h>
#include <Bluetooth/Bluetooth.h>
#include "Countdown/Countdown.h"
#include <Lamp/Lamp.h>

#define REFRESH_TIME 1000

class App {
    private:
        Countdown* mainTimeout;
        BluetoothSerial* bluetoothSerial;
        Bluetooth* bluetooth;
        Lamp* lamp;

    public:
        App();
        void process();
        void init();
        void showBluetoothHelp();
};

#endif
