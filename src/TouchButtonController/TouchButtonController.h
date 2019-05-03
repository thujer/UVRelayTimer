#ifndef touch_button_controller_h
#define touch_button_controller_h

#include <Arduino.h>
#include <TouchButton/TouchButton.h>

class TouchButtonController {
    private:
        TouchButton* touchButton;
        uint8_t pin;

    public:
        TouchButtonController(uint8_t _pin);
        void process();
};


#endif
