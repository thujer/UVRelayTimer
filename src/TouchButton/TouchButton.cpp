/**
    Touch-button
    Purpose: Touch pin monitoring

    @author Tomas Hujer
    @version 0.1 10/04/2019
*/

#include <Arduino.h>

#include "TouchButton/TouchButton.h"

//#define TOUCH_PIN T0 //connected to 4



TouchButton::TouchButton(unsigned char _pin) {

	this->pin = _pin;

	this->touchCountdown = new Countdown();
	this->touchCancelCountdown = new Countdown();

    this->touchValue = 100;
    this->touchState = false;
    this->touchStateLast = false;
    this->touchPressed = false;
	this->pressCounter = 0;
	this->flagCounterActive = false;
}


bool TouchButton::isPressed() {
	if(this->touchPressed) {
		this->touchPressed = false;
		return true;
	} else {
		return false;
	}
}

unsigned char  TouchButton::getPressCount() {
	return this->pressCounter;
}


void TouchButton::process() {
	this->touchValue = touchRead(this->pin);

	if(this->touchCountdown->timeout()) {

		if(this->touchValue < 50) {
			this->touchState = true;
		} else {
			this->touchState = false;
		}

		if(this->touchState != this->touchStateLast) {
			
			if(this->touchState) {
				Serial.println("Button pressed");

				if(!this->pressCounter) {
					this->touchCancelCountdown->set(7000);
					this->flagCounterActive = true;
					Serial.println("flagCounterActive activated");
				}

                this->touchPressed = true;
				this->pressCounter++;


			} else {
				Serial.println("Button released");
			}

			this->touchStateLast = this->touchState;
		}

		this->touchCountdown->set(100);
	} 

	if(this->flagCounterActive) {
		if(this->touchCancelCountdown->timeout()) {
			// Reset counter
			this->pressCounter = 0;
			this->flagCounterActive = false;
			Serial.println("flagCounterActive deactivated");
		}
	}
}
