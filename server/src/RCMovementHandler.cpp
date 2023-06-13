#include <RCMovementHandler.h>

double RCMovementHandler::map_double(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void RCMovementHandler::rotateLeft(int power) {
    analogWrite(back_right_pin, 128-power);
    analogWrite(front_right_pin, 128-power);
    analogWrite(front_left_pin, 128-power);
    analogWrite(back_left_pin, 128-power);  
}

void RCMovementHandler::rotateRight(int power) {
    analogWrite(back_right_pin, 128+power);
    analogWrite(front_right_pin, 128+power);
    analogWrite(front_left_pin, 128+power);
    analogWrite(back_left_pin, 128+power);  
}

void RCMovementHandler::moveLeft(int power) {
    analogWrite(back_right_pin, 128-power);
    analogWrite(front_right_pin, 128+power);
    analogWrite(front_left_pin, 128-power);
    analogWrite(back_left_pin, 128+power);   
}

void RCMovementHandler::moveRight(int power) {
    analogWrite(back_right_pin, 128+power);
    analogWrite(front_right_pin, 128-power);
    analogWrite(front_left_pin, 128+power);
    analogWrite(back_left_pin, 128-power);   
}

void RCMovementHandler::moveForward(int power) {
    analogWrite(back_right_pin, 128-power);
    analogWrite(front_right_pin, 128-power);
    analogWrite(front_left_pin, 128+power);
    analogWrite(back_left_pin, 128+power);  
}

void RCMovementHandler::moveBackward(int power) {
    analogWrite(back_right_pin, 128+power);
    analogWrite(front_right_pin, 128+power);
    analogWrite(front_left_pin, 128-power);
    analogWrite(back_left_pin, 128-power);  
}

void RCMovementHandler::twoDimensionalMove(double x, double y, double turning) {
    double theta = atan2(y, x);
    double power = hypot(x, y);
    
    double sine = sin(theta - PI/4);
    double cosine = cos(theta - PI/4);
    double maximum = max(abs(sine), abs(cosine));

    double leftFront = power * cosine/maximum + turning;
    double rightFront = power * sine/maximum - turning;
    double leftBack = power * sine/maximum + turning;
    double rightBack = power * cosine/maximum - turning;

    if ((power + abs(turning)) > 1) {
        leftFront /= power + abs(turning);
        rightFront /= power + abs(turning);
        leftBack /= power + abs(turning);
        rightBack /= power + abs(turning);
    }
    
    int mappedLeftFront = 128 - map_double(leftFront, -1, 1, -128, 128);
    int mappedRightFront = 128 + map_double(rightFront, -1, 1, -128, 128);
    int mappedLeftBack = 128 - map_double(leftBack, -1, 1, -128, 128);
    int mappedRightBack = 128 + map_double(rightBack, -1, 1, -128, 128);

    analogWrite(back_right_pin, mappedRightBack); 
    analogWrite(front_right_pin, mappedRightFront);
    analogWrite(front_left_pin, mappedLeftFront);
    analogWrite(back_left_pin, mappedLeftBack); 
} 


void RCMovementHandler::move(double x, double y, double turning) {
    if ((x < 0.5) && (x > -0.5) && (y < 0.5) && (y >-0.5)) {
        analogWrite(back_right_pin, 128);
        analogWrite(front_right_pin, 128);
        analogWrite(front_left_pin, 128);
        analogWrite(back_left_pin, 128);
    }
    else {
        twoDimensionalMove(x, y, turning);
    }

}