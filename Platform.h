#ifndef Platform_h
#define Platform_h

#include <Arduino.h>

#define COUNT_PER_CENTIMETER 10.7527f
#define MIN_SPEED 50
#define MAX_SPEED 150

class Platform
{
public:
    Platform(int leftEngineDirectionPin,
             int leftEngineSpeedPin,
             int rightEngineDirectionPin,
             int rightEngineSpeedPin);
    void init();
    void loop();
    void moveForward(int distance);
    void tickLeft();
    void tickRight();

private:
    void reset();
    volatile unsigned int countLeft;
    volatile unsigned int countRight;
    unsigned int distanceCount;
    int leftEngineDirectionPin;
    int leftEngineSpeedPin;
    int rightEngineDirectionPin;
    int rightEngineSpeedPin;
};

#endif
