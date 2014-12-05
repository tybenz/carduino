#include <Car.h>

int sensors[] = {9, 8, 5, 3, 7, 6};
Car* car = new Car(10, 11, 12, sensors);

long friction = 1.0;
int forward = 550;
int stopDelay = 350;
int turn = 340;
boolean go = true;

void setup() {
}

void loop() {
    moveForward();
    turnRight();
}

void moveForward() {
    car->moveForward();
    delay(forward);
    stop();
}

void turnRight() {
    car->turnRight();
    delay(turn);
    stop();
}

void turnLeft() {
    car->turnLeft();
    delay(turn);
    stop();
}

void stop() {
    car->stop();
    delay(stopDelay);
}
