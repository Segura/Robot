#include "Platform.h"

float easyPorabolic(float x)
{
    return -4 * pow(x, 2) + 4 * x;
}

Platform::Platform(int leftEngineDirectionPin,
                   int leftEngineSpeedPin,
                   int rightEngineDirectionPin,
                   int rightEngineSpeedPin)
{
    this->leftEngineDirectionPin = leftEngineDirectionPin;
    this->leftEngineSpeedPin = leftEngineSpeedPin;
    this->rightEngineDirectionPin = rightEngineDirectionPin;
    this->rightEngineSpeedPin = rightEngineSpeedPin;
}

void Platform::init(PlatformSettings settings)
{
    this->settings = settings;

    pinMode(this->leftEngineDirectionPin, OUTPUT);
    pinMode(this->leftEngineSpeedPin, OUTPUT);

    pinMode(this->rightEngineDirectionPin, OUTPUT);
    pinMode(this->rightEngineSpeedPin, OUTPUT);

    this->reset();
}

void Platform::moveForward(int distance)
{
    this->reset();
    this->distanceCount = distance * this->settings.ticksPerCentimeter;
    digitalWrite(this->leftEngineDirectionPin, LOW);
    digitalWrite(this->rightEngineDirectionPin, LOW);
}

void Platform::loop()
{
    this->moveEngine(this->countLeft, this->leftEngineSpeedPin);
    this->moveEngine(this->countRight, this->rightEngineSpeedPin);
}

void Platform::moveEngine(unsigned int engineTicks, int enginePin)
{
    if (engineTicks < this->distanceCount)
    {
        float progress = easyPorabolic(1.0f * engineTicks / this->distanceCount);
        analogWrite(enginePin, max(this->maxSpeed * progress, MIN_SPEED));
    }
    else
    {
        analogWrite(enginePin, 0);
    }
}

void Platform::reset()
{
    this->countLeft = 0;
    this->countRight = 0;
    this->distanceCount = 0;
    this->maxSpeed = min(this->settings.maxSpeed, MAX_SPEED);
    analogWrite(this->leftEngineSpeedPin, 0);
    analogWrite(this->rightEngineSpeedPin, 0);
}

void Platform::tickLeft()
{
    this->countLeft++;
}

void Platform::tickRight()
{
    this->countRight++;
}
