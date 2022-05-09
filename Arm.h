#ifndef Arm_h
#define Arm_h

#include <Servo.h>

#define ARM_ROTATION_MIN_VALUE 0
#define ARM_ROTATION_MAX_VALUE 180
#define ARM_LIFT_MIN_VALUE 10
#define ARM_LIFT_MAX_VALUE 170
#define CLAW_LIFT_MIN_VALUE 10
#define CLAW_LIFT_MAX_VALUE 170
#define CLAW_ROTATION_MIN_VALUE 10
#define CLAW_ROTATION_MAX_VALUE 170
#define CLAW_MIN_VALUE 10
#define CLAW_MAX_VALUE 170

#define NOT_MOVE -1

class Arm
{
public:
    Arm();
    void init(int rotationPin, int armLiftPin, int clawLiftPin, int clawRotationPin, int clawPin);
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
        byte clawAngle,
        long duration);
    void reset();

private:
    bool _manualMode;
    Servo _armRotationServo;
    Servo _armLiftServo;
    Servo _clawLiftServo;
    Servo _clawRotationServo;
    Servo _clawServo;
    long _transitionStart;
    long _transitionEnd;
    long _transitionDuration;
    int _armRotationFrom;
    int _armRotationTo;
    int _armLiftFrom;
    int _armLiftTo;
    int _clawLiftFrom;
    int _clawLiftTo;
    int _clawRotationFrom;
    int _clawRotationTo;
    int _clawFrom;
    int _clawTo;
};

#endif
