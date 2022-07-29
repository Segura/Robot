#ifndef Platform_h
#define Platform_h

#include <Arduino.h>

#define MIN_SPEED 50
#define MAX_SPEED 150

struct PlatformSettings
{
    // PlatformSettings(byte maxSpeed, float ticksPerCentimeter);
    byte maxSpeed;
    float ticksPerCentimeter;
    PlatformSettings();
};

// PlatformSettings::PlatformSettings(byte maxSpeed, float ticksPerCentimeter) {
//     this->maxSpeed = maxSpeed;
//     this->ticksPerCentimeter = ticksPerCentimeter;
// }

class Platform
{
public:
    Platform(int leftEngineDirectionPin,
             int leftEngineSpeedPin,
             int rightEngineDirectionPin,
             int rightEngineSpeedPin);
    void init(PlatformSettings settings);
    void loop();
    void moveForward(int distance);
    void tickLeft();
    void tickRight();

private:
    void reset();
    void moveEngine(unsigned int engineTicks, int enginePin);
    volatile unsigned int countLeft;
    volatile unsigned int countRight;
    PlatformSettings settings;
    byte maxSpeed;
    unsigned int distanceCount;
    int leftEngineDirectionPin;
    int leftEngineSpeedPin;
    int rightEngineDirectionPin;
    int rightEngineSpeedPin;
};

#endif
