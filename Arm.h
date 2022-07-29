#ifndef Arm_h
#define Arm_h

#include <Servo.h>
#include "Component.h"

#define MIN_INPUT_ANGLE 0
#define MAX_INPUT_ANGLE 180

#define DEFAULT_VALUE 90
#define DEFAULT_MIN_VALUE 0
#define DEFAULT_MAX_VALUE 180

#define NOT_MOVE -1

struct ServoSetting
{
    byte min = DEFAULT_MIN_VALUE;
    byte max = DEFAULT_MAX_VALUE;
    byte getCenter()
    {
        return (min + max) / 2;
    }
    ServoSetting(byte _min, byte _max)
    {
        min = _min;
        max = _max;
    }
};

struct ArmSettings
{
    // ArmSettings(ServoSetting armRotation,
    //             ServoSetting armLift,
    //             ServoSetting clawLift,
    //             ServoSetting clawRotation,
    //             ServoSetting claw);
    ServoSetting armRotation;
    ServoSetting armLift;
    ServoSetting clawLift;
    ServoSetting clawRotation;
    ServoSetting claw;
    ArmSettings();
};

// ArmSettings::ArmSettings(ServoSetting armRotation,
//                          ServoSetting armLift,
//                          ServoSetting clawLift,
//                          ServoSetting clawRotation,
//                          ServoSetting claw)
// {
//     this->armRotation = armRotation;
//     this->armLift = armLift;
//     this->clawLift = clawLift;
//     this->clawRotation = clawRotation;
//     this->claw = claw;
// }

class Arm : public Component<ArmSettings>
{
public:
    Arm(int rotationPin, int armLiftPin, int clawLiftPin, int clawRotationPin, int clawPin);
    void init(ArmSettings settings);
    ArmSettings getSettings();
    void attach();
    void detach();
    void loop();
    void manualModeOn();
    void manualModeOff();
    bool isManual();
    void manualMove(
        byte armRotationAngle,
        byte armLiftAngle,
        byte clawLiftAngle,
        byte clawRotationAngle,
        byte clawAngle);
    void moveTo(
        byte armRotationAngle,
        byte armLiftAngle,
        byte clawLiftAngle,
        byte clawRotationAngle,
        long duration);
    void openClaw();
    void closeClaw();
    void reset();

private:
    void writeRaw(Servo servo, ServoSetting, byte angle);
    void writeAnimation(Servo servo, ServoSetting, byte angle);
    byte mapAngle(ServoSetting settings, byte angle);
    ArmSettings settings;
    bool manualMode;
    int rotationPin;
    int armLiftPin;
    int clawLiftPin;
    int clawRotationPin;
    int clawPin;
    Servo armRotationServo;
    Servo armLiftServo;
    Servo clawLiftServo;
    Servo clawRotationServo;
    Servo clawServo;
    long transitionStart;
    long transitionEnd;
    long transitionDuration;
    int armRotationFrom;
    int armRotationTo;
    int armLiftFrom;
    int armLiftTo;
    int clawLiftFrom;
    int clawLiftTo;
    int clawRotationFrom;
    int clawRotationTo;
    int clawFrom;
    int clawTo;
};

#endif
