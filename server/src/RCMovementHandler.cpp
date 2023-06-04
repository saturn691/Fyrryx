#include <headers/RCMovementHandler.h>

// Converts -1 to 1 to 0 to 128
int RCMovementHandler::triggerPressureToPower(double pressure) {
    return (pressure + 1) * 64;
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
    analogWrite(back_right_pin, 128-power);
    analogWrite(front_right_pin, 128+power);
    analogWrite(front_left_pin, 128-power);
    analogWrite(back_left_pin, 128+power);   
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

void RCMovementHandler::move(double x, double y, double turning, double gas) {
    int power = triggerPressureToPower(gas);
    if (x > 0.5) {
        Serial.print("Movement X: "); Serial.print(x);
        moveRight(power);
    }
    else if (x < -0.5) {
        Serial.print("Movement X: "); Serial.print(x);
        moveLeft(power);
    }
    else if (y < -0.5) {
        Serial.print("Movement Y: "); Serial.print(y);
        moveForward(power);
    }
    else if (y > 0.5) {
        Serial.print("Movement Y: "); Serial.print(y);
        moveBackward(power);
    }
    else if (turning > 0.5) {
        Serial.print("Turning: "); Serial.print(turning);
        rotateRight(power);
    }
    else if (turning < -0.5) {
        Serial.print("Turning: "); Serial.print(turning);
        rotateLeft(power);
    }
    else {
        analogWrite(back_right_pin, 128);
        analogWrite(front_right_pin, 128);
        analogWrite(front_left_pin, 128);
        analogWrite(back_left_pin, 128);
    }

}