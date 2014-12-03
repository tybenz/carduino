#include <Shifter.h>
#include <Car.h>

int sensors[] = {8, 9, 2, 3, 4, 5};
Car* car = new Car(10, 11, 12, sensors);

void setup() {
}

int calibrating = 1;

void loop() {
    car->clearShifter();
    delay(1000);
    car->moveForward();
    delay(1000);
}
