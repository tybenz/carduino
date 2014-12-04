#include <Car.h>

int sensors[] = {9, 8, 5, 3, 7, 6};
Car* car = new Car(10, 11, 12, sensors);

void setup() {
}

void loop() {
    car->moveForward();
    delay(1000);
    car->stop();
    delay(250);
    car->turnRight();
    delay(350);
}
