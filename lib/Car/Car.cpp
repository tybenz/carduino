#include <Arduino.h>
#include <Car.h>

#define NUM_REGISTERS 2
#define LEFT_TRIG 0
#define LEFT_ECHO 1
#define RIGHT_TRIG 2
#define RIGHT_ECHO 3
#define FRONT_TRIG 4
#define FRONT_ECHO 5

#define M1_PWMA 0
#define M1_AIN1 1
#define M1_AIN2 2
#define M1_STBY 3
#define M1_BIN1 4
#define M1_BIN2 5
#define M1_PWMB 6
#define M2_PWMA 8
#define M2_AIN1 9
#define M2_AIN2 10
#define M2_STBY 11
#define M2_BIN1 12
#define M2_BIN2 13
#define M2_PWMB 14

Car::Car(int serPin, int rClockPin, int srClockPin, int sensorPins[]) {
    // Pin mode set by shifter lib
    _shifter = new Shifter(serPin, rClockPin, srClockPin, NUM_REGISTERS);

    // Set up sensor pins
    int size = sizeof(sensorPins) / sizeof(int);
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            pinMode(sensorPins[i], OUTPUT);
        } else {
            pinMode(sensorPins[i], INPUT);
        }
        _sensors[i] = sensorPins[i];
    }
}

void Car::moveForward() {
    move(0, 0);
    move(1, 0);
    move(2, 0);
    move(3, 0);
}

void Car::stop() {
    _shifter->setAll(LOW);
    _shifter->setPin(M1_STBY, LOW);
    _shifter->setPin(M2_STBY, LOW);
}

// Move specific motor at speed and direction
// motor: 0 for M1_A 1 for M1_B 2 for M2_A 3 for M2_B
// direction: 0 clockwise, 1 counter-clockwise
void Car::move(int motor, int direction) {
    if (motor < 3) {
        _shifter->setPin(M1_STBY, HIGH);
    } else {
        _shifter->setPin(M2_STBY, HIGH);
    }

    boolean inPin1 = LOW;
    boolean inPin2 = HIGH;

    if (direction == 1) {
        inPin1 = HIGH;
        inPin2 = LOW;
    }

    if (motor == 0) {
        _shifter->setPin(M1_AIN1, inPin1);
        _shifter->setPin(M1_AIN2, inPin2);
        _shifter->setPin(M1_PWMA, HIGH);
    } else if (motor == 1) {
        _shifter->setPin(M1_BIN1, inPin1);
        _shifter->setPin(M1_BIN2, inPin2);
        _shifter->setPin(M1_PWMB, HIGH);
    } else if (motor == 2) {
        _shifter->setPin(M2_AIN1, inPin1);
        _shifter->setPin(M2_AIN2, inPin2);
        _shifter->setPin(M2_PWMA, HIGH);
    } else {
        _shifter->setPin(M2_BIN1, inPin1);
        _shifter->setPin(M2_BIN2, inPin2);
        _shifter->setPin(M2_PWMB, HIGH);
    }
}

void Car::turnRight() {

}

void Car::turnLeft() {

}

void Car::calibrate() {

}

int Car::leftTrig() {
    return _sensors[LEFT_TRIG];
}

int Car::leftEcho() {
    return _sensors[LEFT_ECHO];
}

int Car::rightTrig() {
    return _sensors[RIGHT_TRIG];
}

int Car::rightEcho() {
    return _sensors[RIGHT_ECHO];
}

int Car::frontTrig() {
    return _sensors[FRONT_TRIG];
}

int Car::frontEcho() {
    return _sensors[FRONT_ECHO];
}
