#include "Platform.h"

float easyPorabolic(float x)
{
    return -4 * pow(x, 2) + 4 * x;
}

Platform::Platform() {}

void Platform::init(
    int leftEngineDirectionPin,
    int leftEngineSpeedPin,
    int rightEngineDirectionPin,
    int rightEngineSpeedPin)
{
    this->_leftEngineDirectionPin = leftEngineDirectionPin;
    this->_leftEngineSpeedPin = leftEngineSpeedPin;
    this->_rightEngineDirectionPin = rightEngineDirectionPin;
    this->_rightEngineSpeedPin = rightEngineSpeedPin;

    pinMode(leftEngineDirectionPin, OUTPUT);
    pinMode(leftEngineSpeedPin, OUTPUT);

    pinMode(rightEngineDirectionPin, OUTPUT);
    pinMode(rightEngineSpeedPin, OUTPUT);

    this->reset();
}

void Platform::moveForward(int distance)
{
    this->reset();
    this->distanceCount = distance * COUNT_PER_CENTIMETER;
    digitalWrite(this->_leftEngineDirectionPin, LOW);
    digitalWrite(this->_rightEngineDirectionPin, LOW);
}

void Platform::loop()
{
    if (this->countLeft < this->distanceCount)
    {
        float progress = easyPorabolic(1.0f * this->countLeft / this->distanceCount);
        analogWrite(this->_leftEngineSpeedPin, max(MAX_SPEED * progress, MIN_SPEED));
    }
    else
    {
        analogWrite(this->_leftEngineSpeedPin, 0);
    }
    if (this->countRight < this->distanceCount) {
        float progress = easyPorabolic(1.0f * this->countRight / this->distanceCount);
        analogWrite(this->_rightEngineSpeedPin, max(MAX_SPEED * progress, MIN_SPEED));
    } else {
        analogWrite(this->_rightEngineSpeedPin, 0);
    }
}

void Platform::reset()
{
    this->countLeft = 0;
    this->countRight = 0;
    this->distanceCount = 0;
    analogWrite(this->_leftEngineSpeedPin, 0);
    analogWrite(this->_rightEngineSpeedPin, 0);
}

void Platform::tickLeft()
{
    this->countLeft++;
}

void Platform::tickRight()
{
    this->countRight++;
}
