
#include <Lamp/Lamp.h>

Lamp::Lamp(unsigned char pinRelay) {
    this->pinRelay = pinRelay;
    this->timeout = new Countdown();
    this->state = 0;
    
    pinMode (this->pinRelay, OUTPUT);
}


void Lamp::on() {
    Serial.println("Lamp on");
    digitalWrite(this->pinRelay, HIGH);
}


void Lamp::off() {
    Serial.println("Lamp off");
    digitalWrite(this->pinRelay, LOW);
}


void Lamp::stop() {
    Serial.println("Lamp stop");
    this->off();
    this->state = 0;
}



void Lamp::shineDuration(unsigned int duration) {

    Serial.printf("Lamp on for %d sec\r\n", duration);

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
            this->stop();
        }
    }

}

