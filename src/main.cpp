/*Program to control LED (ON/OFF) from ESP32 using Serial Bluetooth
 * Thanks to Neil Kolbans for his efoorts in adding the support to Arduino IDE
 * Turotial on: www.circuitdigest.com
 */

/*
#include "BluetoothSerial.h"  //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT;  // Object for Bluetooth

char incomingChar = 0;
byte pinRelay = 5;
String incomingCommand = "";

void setup() {
    Serial.begin(115200);
    ESP_BT.begin("ESP32_Relay_Control");  // Name of your Bluetooth Signal
    Serial.println("Bluetooth Device is Ready to Pair");

    pinMode(pinRelay, OUTPUT);  // Specify that LED pin is output
}

void loop() {
    if (ESP_BT.available()) {
        
		incomingChar = ESP_BT.read();  

		if(incomingChar == 0) {
			Serial.print("Received:");
			Serial.println(incomingCommand);

			if(incomingCommand == "on") {
				digitalWrite(pinRelay, HIGH);
				ESP_BT.println("Lamp turned ON");
			}

			if(incomingCommand == "off") {
				digitalWrite(pinRelay, LOW);
				ESP_BT.println("Lamp turned OFF");
			}

			incomingCommand = "";

		} else {
			incomingCommand += incomingChar;
		}

    }
}

*/




using namespace std;

#include <App/App.h>

/**
 * Create App instance
 */
App* app = new App();


/**
 * Arduino init function
 */ 
void setup() {
	app->init();
}


/**
 * Arduino loop function
 */ 
void loop() {
	app->process();
}
