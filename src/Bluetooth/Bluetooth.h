
#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <Arduino.h>
#include <BluetoothSerial.h>

class Bluetooth {
    private:
        BluetoothSerial* bluetoothSerial;
        const char* deviceName;
        String message;
        bool messageReady;

    public:
        Bluetooth(const char* name);
        void setup();
        void process();
        bool isMessageReady();
        String getMessage();
        BluetoothSerial* getInstance();
};

#endif
