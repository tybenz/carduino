#include <Car.h>

#define FRONT 0
#define RIGHT 1
#define LEFT 2

int sensors[] = {9, 8, 5, 3, 7, 6};
Car* car = new Car(10, 11, 12, sensors);

int forward = 470;
int stopDelay = 400;
int turn = 555;
int pleaseStop = 0;

void setup() {
}

void loop() {
    if ( !pleaseStop ) {
    //BEGIN
        moveForward();
        turnRight();
        moveForward();
        moveForward();
        moveForward();
        turnLeft();
        moveForward();
        moveForward();
        moveForward();
        //END
        pleaseStop = 1;
    } else {
        stop();
    }
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

long ping(int sensor) {
    long duration, inches, cm;
    int trigPin, echoPin;

    if (sensor == 0) {
        trigPin = 7;
        echoPin = 8;
    } else if (sensor == 1) {
        trigPin = 5;
        echoPin = 6;
    } else if (sensor == 2) {
        trigPin = 3;
        echoPin = 4;
    }

    // Sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose duration is the time
    // (in microseconds) from the sending of the ping to the reception of its
    // echo off of an object
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    // convert the time into a distance
    inches = microsecondsToInches(duration);

    return inches;
}

long microsecondsToInches(long microseconds) {
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
    // second).  This gives the distance travelled by the ping, outbound
    // and return, so we divide by 2 to get the distance of the obstacle.
    // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
    return microseconds / 74 / 2;
}
