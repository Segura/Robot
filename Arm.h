#ifndef Arm_h
#define Arm_h
#include <Servo.h>

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
