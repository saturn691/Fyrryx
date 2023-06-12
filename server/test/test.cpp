#include <math.h>
#include <cmath>
#include <iostream>

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void twoDimensionalMove(double x, double y, double turning) {
    double theta = atan2(y, x);
    double power = hypot(x, y);
    
    double sine = sin(theta - M_PI/4);
    double cosine = cos(theta - M_PI/4);
    double maximum = std::max(abs(sine), abs(cosine));

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
    std::cout << leftFront << std::endl;

    int mappedLeftFront = 128 - map(leftFront, -1, 1, -128, 128);
    int mappedRightFront = 128 + map(rightFront, -1, 1, -128, 128);
    int mappedLeftBack = 128 - map(leftBack, -1, 1, -128, 128);
    int mappedRightBack = 128 + map(rightBack, -1, 1, -128, 128);
    
    std::cout << "Cosine of angle = " << cosine << std::endl;
    std::cout << "Sine of angle = " << sine << std::endl << std::endl;

    std::cout << "Left Front: " << mappedLeftFront << std::endl;
    std::cout << "Right Front: " << mappedRightFront << std::endl;
    std::cout << "Left Back: " << mappedLeftBack << std::endl;
    std::cout << "Right Back: " << mappedRightBack << std::endl;
}


int main(int argc, char* argv[]) {
    twoDimensionalMove(0,0,1);

    return 0;
}