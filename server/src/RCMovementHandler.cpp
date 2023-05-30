#include <headers/RCMovementHandler.h>

// Converts -1 to 1 to 0 to 255
int RCMovementHandler::triggerPressureToPower(double pressure) {
    return (pressure + 1) * 127.5;
}

void RCMovementHandler::moveForward(int power) {
    analogWrite(back_right_pin, -power);
    analogWrite(front_right_pin, -power);
    analogWrite(front_left_pin, -power);
    analogWrite(back_left_pin, -power);  
}

void RCMovementHandler::moveBackward(int power) {
    analogWrite(back_right_pin, power);
    analogWrite(front_right_pin, power);
    analogWrite(front_left_pin, power);
    analogWrite(back_left_pin, power);  
}

void RCMovementHandler::moveLeft(int power) {
    analogWrite(back_right_pin, -power);
    analogWrite(front_right_pin, power);
    analogWrite(front_left_pin, power);
    analogWrite(back_left_pin, -power);   
}

void RCMovementHandler::moveRight(int power) {
    analogWrite(back_right_pin, power);
    analogWrite(front_right_pin, -power);
    analogWrite(front_left_pin, -power);
    analogWrite(back_left_pin, power);   
}

void RCMovementHandler::rotateLeft(int power) {
    analogWrite(back_right_pin, -power);
    analogWrite(front_right_pin, -power);
    analogWrite(front_left_pin, power);
    analogWrite(back_left_pin, power);  
}

void RCMovementHandler::rotateRight(int power) {
    analogWrite(back_right_pin, power);
    analogWrite(front_right_pin, power);
    analogWrite(front_left_pin, -power);
    analogWrite(back_left_pin, -power);  
}

void RCMovementHandler::move(std::unordered_map<std::string, double> data) {
    if (!data.empty()) return;
 

    int power = triggerPressureToPower(data["Gas"]);
    if (data["Movement X"] > 0.5) {
        // Serial.print("Movement X: "); Serial.print(data["Movement X"]);
        moveRight(power);
    }
    else if (data["Movement X"] < -0.5) {
        // Serial.print("Movement X: "); Serial.print(data["Movement X"]);
        moveLeft(power);
    }
    else if (data["Movement Y"] < -0.5) {
        // Serial.print("Movement Y: "); Serial.print(data["Movement Y"]);
        moveBackward(power);
    }
    else if (data["Movement Y"] > 0.5) {
        // Serial.print("Movement Y: "); Serial.print(data["Movement Y"]);
        moveForward(power);
    }

}