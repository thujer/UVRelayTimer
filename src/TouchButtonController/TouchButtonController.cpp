/**
    TouchButtonController
    Purpose: Touch button events controller

    @author Tomas Hujer
    @version 0.1 10/04/2019 
*/

#include <TouchButtonController/TouchButtonController.h>

TouchButtonController::TouchButtonController(uint8_t _pin) {

	this->pin = _pin;

	// Capacitive touch button
	this->touchButton = new TouchButton(this->pin);

}


/**
 * TODO: move it into SystemAPI and finish Storage class
 */
/*
void App::resetToFactorySettings() {
	
	Serial.println("Doing configuration reset to factory defaults...");

	// TODO: wait for done !!!
	this->processController->stopCriticalProcesses();
	
	this->wifiController->clearStoredConfig();

	delay(1000);
	Chip::softwareRestart();
}
*/



void TouchButtonController::process() {

    this->touchButton->process();

	if(touchButton->isPressed()) {

		// Switch leds phases
		if(touchButton->getPressCount() & 1) {
		} else {
		}

		if(touchButton->getPressCount() > 3) {
			/*
			this->ledEthernet->flash(500);
			this->ledWifi->flash(500);
			this->systemApi->resetToFactoryDefault();
			*/
		}
	}

}
