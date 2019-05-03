
#include <Bluetooth/Bluetooth.h>


Bluetooth::Bluetooth(const char* name) {

    this->bluetoothSerial = new BluetoothSerial();

    this->deviceName = name;
    this->messageReady = false;
    this->message = "";

    #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
    #endif

}


void Bluetooth::setup() {
    this->bluetoothSerial->begin(this->deviceName); 
}


String Bluetooth::getMessage() {
    String message = this->message;
    this->message = "";
    this->messageReady = false;
    return message;
}


bool Bluetooth::isMessageReady() {
    return this->messageReady;
}


 BluetoothSerial* Bluetooth::getInstance() {
    return this->bluetoothSerial;
}


void Bluetooth::process() {

    if (this->bluetoothSerial->available()) {
        char incomingChar = this->bluetoothSerial->read();

		if((incomingChar == 0) || 
           (incomingChar == 13)) {

            this->messageReady = true;

		} else {
            if(!this->messageReady) {
                this->message += incomingChar;
            }
		}
    } 

}

