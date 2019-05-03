
#ifndef touch_button_connection_h_
#define touch_button_connection_h_

#include <Countdown/Countdown.h>

/*
static const uint8_t T0 = 4;
static const uint8_t T1 = 0;
static const uint8_t T2 = 2;
static const uint8_t T3 = 15;
static const uint8_t T4 = 13;
static const uint8_t T5 = 12;
static const uint8_t T6 = 14;
static const uint8_t T7 = 27;
static const uint8_t T8 = 33;
static const uint8_t T9 = 32;
*/


//#define TOUCH_PIN T0 //connected to 4


class TouchButton {

private:
    int touchValue;
    bool touchState;
    bool touchStateLast;
    bool touchPressed;

    unsigned char pressCounter;
    bool flagCounterActive;

    Countdown* touchCountdown;
    Countdown* touchCancelCountdown;

    unsigned char pin;

public:
    TouchButton(unsigned char _pin);
    void process();
    bool isPressed();
    unsigned char getPressCount();
};


#endif
