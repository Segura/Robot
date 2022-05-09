#include "Arm.h"

#define DEFAULT_POSITION 90

float easyInOut(float x)
{
    return -(cos(PI * x) - 1) / 2;
}

Arm::Arm() {}

void Arm::init(int rotationPin, int armLiftPin, int clawLiftPin, int clawRotationPin, int clawPin)
{
    this->manualModeOff();

    this->_armRotationServo.write(DEFAULT_POSITION);
    this->_armLiftServo.write(DEFAULT_POSITION);
    this->_clawLiftServo.write(DEFAULT_POSITION);
    this->_clawRotationServo.write(DEFAULT_POSITION);
    this->_clawServo.write(DEFAULT_POSITION);

    this->_armRotationServo.attach(rotationPin);
    this->_armLiftServo.attach(armLiftPin);
    this->_clawLiftServo.attach(clawLiftPin);
    this->_clawRotationServo.attach(clawRotationPin);
    this->_clawServo.attach(clawPin);
}

void Arm::manualModeOn()
{
    this->_manualMode = true;
}

void Arm::manualModeOff()
{
    this->_manualMode = false;
}

bool Arm::isManual()
{
    return this->_manualMode;
}

void Arm::manualMove(byte armRotationAngle,
                     byte armLiftAngle,
                     byte clawLiftAngle,
                     byte clawRotationAngle,
                     byte clawAngle)
{
    if (this->_manualMode)
    {
        this->_armRotationServo.write(constrain(armRotationAngle, ARM_ROTATION_MIN_VALUE, ARM_ROTATION_MAX_VALUE));
        this->_armLiftServo.write(constrain(armLiftAngle, ARM_LIFT_MIN_VALUE, ARM_LIFT_MAX_VALUE));
        this->_clawLiftServo.write(constrain(clawLiftAngle, CLAW_LIFT_MIN_VALUE, CLAW_LIFT_MAX_VALUE));
        this->_clawRotationServo.write(constrain(clawRotationAngle, CLAW_ROTATION_MIN_VALUE, CLAW_ROTATION_MAX_VALUE));
        this->_clawServo.write(clawAngle);
    }
}

void Arm::moveTo(byte armRotationAngle,
                 byte armLiftAngle,
                 byte clawLiftAngle,
                 byte clawRotationAngle,
                 byte clawAngle,
                 long duration)
{
    if (!this->_manualMode)
    {
        this->_transitionStart = millis();
        this->_transitionDuration = constrain(duration, 1000, 10000);
        this->_transitionEnd = this->_transitionStart + this->_transitionDuration;

        if (armRotationAngle > NOT_MOVE)
        {
            this->_armRotationFrom = this->_armRotationServo.read();
            this->_armRotationTo = constrain(armRotationAngle, ARM_ROTATION_MIN_VALUE, ARM_ROTATION_MAX_VALUE);
        }
        if (armLiftAngle > NOT_MOVE)
        {
            this->_armLiftFrom = this->_armLiftServo.read();
            this->_armLiftTo = constrain(armLiftAngle, ARM_LIFT_MIN_VALUE, ARM_LIFT_MAX_VALUE);
        }
        if (clawLiftAngle > NOT_MOVE)
        {
            this->_clawLiftFrom = this->_clawLiftServo.read();
            this->_clawLiftTo = constrain(clawLiftAngle, CLAW_LIFT_MIN_VALUE, CLAW_LIFT_MAX_VALUE);
        }
        if (clawRotationAngle > NOT_MOVE)
        {
            this->_clawRotationFrom = this->_clawRotationServo.read();
            this->_clawRotationTo = constrain(clawRotationAngle, CLAW_ROTATION_MIN_VALUE, CLAW_ROTATION_MAX_VALUE);
        }
    }
}

void Arm::loop()
{
    long currentTime = millis();
    if (currentTime > this->_transitionEnd)
    {
        return;
    }
    long timePassed = currentTime - this->_transitionStart;
    float progress = easyInOut(1.0f * timePassed / this->_transitionDuration);
    this->_armRotationServo.write(this->_armRotationFrom + (this->_armRotationTo - this->_armRotationFrom) * progress);
    this->_armLiftServo.write(this->_armLiftFrom + (this->_armLiftTo - this->_armLiftFrom) * progress);
    this->_clawLiftServo.write(this->_clawLiftFrom + (this->_clawLiftTo - this->_clawLiftFrom) * progress);
    this->_clawRotationServo.write(this->_clawRotationFrom + (this->_clawRotationTo - this->_clawRotationFrom) * progress);
}

void Arm::reset()
{
    this->moveTo(DEFAULT_POSITION, DEFAULT_POSITION, DEFAULT_POSITION, DEFAULT_POSITION, DEFAULT_POSITION, 1000);
}
