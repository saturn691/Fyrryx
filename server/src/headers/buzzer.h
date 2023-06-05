#ifndef _BUZZER_h
#define _BUZZER_h

#include <Arduino.h>

class Buzzer {
private:
    int last_buzz_time;

    void play(int buzzer_pin, int rhythm[], int melody[]);

public:
    Buzzer();

    void horn(int buzzer_pin);
    void rickroll_intro(int buzzer_pin);
    void rickroll_chorus(int buzzer_pin);
};

#endif