#include <Car.h>

int sensors[] = {9, 8, 5, 3, 7, 6};
Car* car = new Car(10, 11, 12, sensors);

long friction = 1.0;
int forward = 1000 * friction;
int stop = 250 * friction;
int turn = 300 * friction;

void setup() {
}

void loop() {
    car->moveForward();
    delay(forward);
    car->stop();
    delay(stop);
    car->turnRight();
    delay(turn);
}
