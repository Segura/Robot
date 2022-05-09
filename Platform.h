#ifndef Platform_h
#define Platform_h

#include <Arduino.h>

#define COUNT_PER_CENTIMETER 10.7527f
#define MIN_SPEED 50
#define MAX_SPEED 150

class Platform
{
public:
    Platform();
    void init(int leftEngineDirectionPin,
              int leftEngineSpeedPin,
              int rightEngineDirectionPin,
              int rightEngineSpeedPin);
    void loop();
    void moveForward(int distance);
    void tickLeft();
    void tickRight();

private:
    void reset();
    volatile unsigned int countLeft;
    volatile unsigned int countRight;
    unsigned int distanceCount;
    int _leftEngineDirectionPin;
    int _leftEngineSpeedPin;
    int _rightEngineDirectionPin;
    int _rightEngineSpeedPin;
};

#endif
