#include <headers/RCMovementHandler.h>

// Converts 0 to 1 to 0 to 128
int RCMovementHandler::magnitudeToPower(double x, double y) {
    int value = std::sqrt(x * x + y * y) * 128;
    
    if (value >= 128) {
        return 128;
    }
    else {
        return value;
    }
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

void RCMovementHandler::move(double x, double y, double turning) {
    int power = magnitudeToPower(x, y);
    if (x > 0.5) {
        Serial.println("Movement X: "); Serial.print(x);
        moveRight(power);
    }
    else if (x < -0.5) {
        Serial.println("Movement X: "); Serial.print(x);
        moveLeft(power);
    }
    else if (y < -0.5) {
        Serial.println("Movement Y: "); Serial.print(y);
        moveForward(power);
    }
    else if (y > 0.5) {
        Serial.println("Movement Y: "); Serial.print(y);
        moveBackward(power);
    }
    else if (turning > 0.5) {
        Serial.println("Turning: "); Serial.print(turning);
        power = magnitudeToPower(turning, 0);
        rotateRight(power);
    }
    else if (turning < -0.5) {
        power = magnitudeToPower(turning, 0);
        Serial.println("Turning: "); Serial.print(turning);
        rotateLeft(power);
    }
    else {
        analogWrite(back_right_pin, 128);
        analogWrite(front_right_pin, 128);
        analogWrite(front_left_pin, 128);
        analogWrite(back_left_pin, 128);
    }

}