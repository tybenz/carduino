#ifndef Car_h
#define Car_h

#include <Arduino.h>
#include <Shifter.h>

class Car
{
    public:
        Car(int serPin, int rClockPin, int srClockPin, int sensorPins[]);
        void moveForward();
        void turnRight();
        void turnLeft();
        void calibrate();
        void stop();
        void clearShifter();
        long pingLeft();
        long pingRight();
        long pingFront();

    private:
        Shifter* _shifter;
        int _sensors[];
        int leftTrig();
        int leftEcho();
        int rightTrig();
        int rightEcho();
        int frontTrig();
        int frontEcho();
        void move(int motor, int direction);
        long ping(int direction);
};

#endif //Car_h
