#include "Arm.h"

float easyInOut(float x)
{
    return -(cos(PI * x) - 1) / 2;
}

Arm::Arm(int rotationPin, int armLiftPin, int clawLiftPin, int clawRotationPin, int clawPin)
{
    this->rotationPin = rotationPin;
    this->armLiftPin = armLiftPin;
    this->clawLiftPin = clawLiftPin;
    this->clawRotationPin = clawRotationPin;
    this->clawPin = clawPin;
}

void Arm::init(ArmSettings settings)
{
    this->manualModeOff();

    this->settings = settings;

    // TODO: перенести в attach
    this->armRotationServo.write(settings.armRotation.getCenter());
    this->armLiftServo.write(settings.armLift.getCenter());
    this->clawLiftServo.write(settings.clawLift.getCenter());
    this->clawRotationServo.write(settings.clawRotation.getCenter());
    this->clawServo.write(settings.claw.getCenter());
}

ArmSettings Arm::getSettings()
{
    return this->settings;
}

void Arm::attach()
{
    this->armRotationServo.attach(rotationPin);
    this->armLiftServo.attach(armLiftPin);
    this->clawLiftServo.attach(clawLiftPin);
    this->clawRotationServo.attach(clawRotationPin);
    this->clawServo.attach(clawPin);
}

void Arm::detach()
{
    this->armRotationServo.detach();
    this->armLiftServo.detach();
    this->clawLiftServo.detach();
    this->clawRotationServo.detach();
    this->clawServo.detach();
}

void Arm::manualModeOn()
{
    this->manualMode = true;
}

void Arm::manualModeOff()
{
    this->manualMode = false;
}

bool Arm::isManual()
{
    return this->manualMode;
}

void Arm::startCalibration(){

};

void Arm::calibrating(int value){

};

bool Arm::nextCalibrationStep()
{
    return false;
};

void Arm::stopValibrating(){

};

void Arm::manualMove(byte armRotationAngle,
                     byte armLiftAngle,
                     byte clawLiftAngle,
                     byte clawRotationAngle,
                     byte clawAngle)
{
    if (this->manualMode)
    {
        this->writeRaw(this->armRotationServo, this->settings.armRotation, armRotationAngle);
        this->writeRaw(this->armLiftServo, this->settings.armLift, armLiftAngle);
        this->writeRaw(this->clawLiftServo, this->settings.clawLift, clawLiftAngle);
        this->writeRaw(this->clawRotationServo, this->settings.clawRotation, clawRotationAngle);
        this->writeRaw(this->clawServo, this->settings.claw, clawAngle);
    }
}

void Arm::moveTo(byte armRotationAngle,
                 byte armLiftAngle,
                 byte clawLiftAngle,
                 byte clawRotationAngle,
                 long duration)
{
    if (!this->manualMode)
    {
        this->transitionStart = millis();
        this->transitionDuration = constrain(duration, 1000, 10000);
        this->transitionEnd = this->transitionStart + this->transitionDuration;

        this->writeAnimation(this->armRotationServo, this->settings.armLift, armRotationAngle);
        this->writeAnimation(this->armLiftServo, this->settings.armLift, armLiftAngle);
        this->writeAnimation(this->clawLiftServo, this->settings.clawLift, clawLiftAngle);
        this->writeAnimation(this->clawRotationServo, this->settings.clawRotation, clawRotationAngle);
    }
}

void Arm::writeRaw(Servo servo, ServoSetting settings, byte angle)
{
    servo.write(this->mapAngle(settings, angle));
}

void Arm::writeAnimation(Servo servo, ServoSetting settings, byte angle)
{
    if (angle > NOT_MOVE)
    {
        this->armRotationFrom = servo.read();
        this->armRotationTo = this->mapAngle(settings, angle);
    }
}

byte Arm::mapAngle(ServoSetting settings, byte angle)
{
    return map(angle, MIN_INPUT_ANGLE, MAX_INPUT_ANGLE, settings.min, settings.max);
}

void Arm::loop()
{
    long currentTime = millis();
    if (currentTime > this->transitionEnd)
    {
        return;
    }
    long timePassed = currentTime - this->transitionStart;
    float progress = easyInOut(1.0f * timePassed / this->transitionDuration);
    this->armRotationServo.write(this->armRotationFrom + (this->armRotationTo - this->armRotationFrom) * progress);
    this->armLiftServo.write(this->armLiftFrom + (this->armLiftTo - this->armLiftFrom) * progress);
    this->clawLiftServo.write(this->clawLiftFrom + (this->clawLiftTo - this->clawLiftFrom) * progress);
    this->clawRotationServo.write(this->clawRotationFrom + (this->clawRotationTo - this->clawRotationFrom) * progress);
}

void Arm::openClaw()
{
    this->clawServo.write(this->settings.claw.max);
}

void Arm::closeClaw()
{
    this->clawServo.write(this->settings.claw.min);
}

void Arm::reset()
{
    this->moveTo(
        this->settings.armRotation.getCenter(),
        this->settings.armLift.getCenter(),
        this->settings.clawLift.getCenter(),
        this->settings.clawRotation.getCenter(),
        1000);
    this->openClaw();
}
