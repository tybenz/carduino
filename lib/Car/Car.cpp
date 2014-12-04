#include <Car.h>

#define NUM_REGISTERS 2
#define LEFT_TRIG 0
#define LEFT_ECHO 1
#define RIGHT_TRIG 2
#define RIGHT_ECHO 3
#define FRONT_TRIG 4
#define FRONT_ECHO 5

#define M1_PWMA 0
#define M1_AIN1 2
#define M1_AIN2 1
#define M1_STBY 3
#define M1_BIN1 4
#define M1_BIN2 5
#define M1_PWMB 6

#define M2_PWMA 8
#define M2_AIN1 10
#define M2_AIN2 9
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

    clearShifter();
}

void Car::moveForward() {
    move(0, 1);
    move(1, 1);
    move(2, 1);
    move(3, 1);
}

void Car::clearShifter() {
    _shifter->clear();
    _shifter->write();
}

void Car::stop() {
    _shifter->clear();
    _shifter->setPin(M1_STBY, LOW);
    _shifter->setPin(M2_STBY, LOW);
    _shifter->write();
}

void Car::turnRight() {
    move(0, 1);
    move(1, 1);
    move(2, 0);
    move(3, 0);
}

void Car::turnLeft() {
    move(0, 0);
    move(1, 0);
    move(2, 1);
    move(3, 1);
}

void Car::calibrate() {
}

long Car::pingLeft() {
    return ping(0);
}

long Car::pingRight() {
    return ping(1);
}

long Car::pingFront() {
    return ping(2);
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

    boolean inPin1A = LOW;
    boolean inPin2A = HIGH;
    boolean inPin1B = HIGH;
    boolean inPin2B = LOW;

    if (direction == 1) {
        inPin1A = HIGH;
        inPin2A = LOW;
        inPin1B = LOW;
        inPin2B = HIGH;
    }

    if (motor == 0) {
        _shifter->setPin(M1_AIN1, inPin1A);
        _shifter->setPin(M1_AIN2, inPin2A);
        _shifter->setPin(M1_PWMA, HIGH);
    } else if (motor == 1) {
        _shifter->setPin(M1_BIN1, inPin1B);
        _shifter->setPin(M1_BIN2, inPin2B);
        _shifter->setPin(M1_PWMB, HIGH);
    } else if (motor == 2) {
        _shifter->setPin(M2_AIN1, inPin1A);
        _shifter->setPin(M2_AIN2, inPin2A);
        _shifter->setPin(M2_PWMA, HIGH);
    } else {
        _shifter->setPin(M2_BIN1, inPin1B);
        _shifter->setPin(M2_BIN2, inPin2B);
        _shifter->setPin(M2_PWMB, HIGH);
    }
    _shifter->write();
}

// Ping left/right/forward - returns long distance
// direction: 0 for LEFT 1 for RIGHT 2 for FRONT
long Car::ping(int direction) {
    int trigPin, echoPin;
    long duration;

    if (direction == 0) {
        trigPin = leftTrig();
        echoPin = leftEcho();
    } else if (direction == 1) {
        trigPin = rightTrig();
        echoPin = rightEcho();
    } else if (direction == 2) {
        trigPin = frontTrig();
        echoPin = frontEcho();
    }

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    return (duration/2) / 29.1;
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
