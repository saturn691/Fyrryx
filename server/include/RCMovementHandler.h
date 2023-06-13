#ifndef _RCMOVEMENTHANDLER_h
#define _RCMOVEMENTHANDLER_h

#include <Arduino.h>
#include <unordered_map>

class RCMovementHandler {
private:
    int back_right_pin;
    int front_right_pin;    
    int front_left_pin;
    int back_left_pin;

    double map_double(double x, double in_min, double in_max, double out_min, double out_max);
    void twoDimensionalMove(double x, double y, double steering);
    void moveForward(int power);
    void moveBackward(int power);
    void moveLeft(int power);
    void moveRight(int power);
    void rotateLeft(int power);
    void rotateRight(int power);
public:
    RCMovementHandler(int br, int fr, int fl, int bl): back_right_pin(br), front_right_pin(fr), front_left_pin(fl), back_left_pin(bl) {};
    
    void move(double x, double y, double turning);
};

#endif