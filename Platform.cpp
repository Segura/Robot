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

void Platform::init()
{
    pinMode(this->leftEngineDirectionPin, OUTPUT);
    pinMode(this->leftEngineSpeedPin, OUTPUT);

    pinMode(this->rightEngineDirectionPin, OUTPUT);
    pinMode(this->rightEngineSpeedPin, OUTPUT);

    this->reset();
}

void Platform::moveForward(int distance)
{
    this->reset();
    this->distanceCount = distance * COUNT_PER_CENTIMETER;
    digitalWrite(this->leftEngineDirectionPin, LOW);
    digitalWrite(this->rightEngineDirectionPin, LOW);
}

void Platform::loop()
{
    if (this->countLeft < this->distanceCount)
    {
        float progress = easyPorabolic(1.0f * this->countLeft / this->distanceCount);
        analogWrite(this->leftEngineSpeedPin, max(MAX_SPEED * progress, MIN_SPEED));
    }
    else
    {
        analogWrite(this->leftEngineSpeedPin, 0);
    }
    if (this->countRight < this->distanceCount)
    {
        float progress = easyPorabolic(1.0f * this->countRight / this->distanceCount);
        analogWrite(this->rightEngineSpeedPin, max(MAX_SPEED * progress, MIN_SPEED));
    }
    else
    {
        analogWrite(this->rightEngineSpeedPin, 0);
    }
}

void Platform::reset()
{
    this->countLeft = 0;
    this->countRight = 0;
    this->distanceCount = 0;
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
