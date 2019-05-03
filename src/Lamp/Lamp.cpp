
#include <Lamp/Lamp.h>

Lamp::Lamp(unsigned char pinRelay, BluetoothSerial* _bluetooth) {

    this->bluetooth = _bluetooth;

    this->pinRelay = pinRelay;
    this->timeout = new Countdown();
    this->state = 0;
    this->currentState = 0;
    
    pinMode (this->pinRelay, OUTPUT);
}


void Lamp::on() {
    Serial.println("Lamp on");
    this->bluetooth->println("Lamp on");

    digitalWrite(this->pinRelay, HIGH);
}


void Lamp::off() {
    Serial.println("Lamp off");
    this->bluetooth->println("Lamp off");

    digitalWrite(this->pinRelay, LOW);
}


void Lamp::stop() {
    Serial.println("Lamp stop");
    this->bluetooth->println("Lamp stop");

    this->off();
    this->state = 0;
}


void Lamp::pause() {
    Serial.println("Lamp pause");
    this->bluetooth->println("Lamp paused");

    this->currentState = this->timeout->get();
    this->off();
    this->state = 0;
}


void Lamp::resume() {
    Serial.println("Lamp resume");
    this->bluetooth->println("Lamp resume");

    this->timeout->set(this->currentState);
    this->on();
    this->state = 1;
}


void Lamp::shineDuration(unsigned int duration) {

    Serial.printf("Lamp on for %d sec\r\n", duration);
    this->bluetooth->printf("Lamp on for %d sec\r\n", duration);

    this->timeout->set(duration);
    this->on();
    this->state = 1;
}


unsigned char Lamp::getRunningState() {
    return this->state;
}


unsigned long Lamp::getTimeLeft() {
    return this->timeout->get();
}


void Lamp::process() {

    if(this->state) {
        if(this->timeout->timeout()) {
            Serial.println("Lamp timeout -> stop");
            this->bluetooth->println("Lamp timeout -> stop");
            this->stop();
        }
    }

}

