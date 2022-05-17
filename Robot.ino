#include <Bounce2.h>
#include <ezLED.h>
#include "Defines.h"
#include "Arm.h"
#include "Platform.h"
#include "Calibrator.h"

Arm arm = Arm(ARM_ROTATION_SERVO_PIN, ARM_LIFT_SERVO_PIN, CLAW_LIFT_SERVO_PIN, CLAW_ROTATION_SERVO_PIN, CLAW_SERVO_PIN);
Platform platform = Platform(LEFT_ENGINE_DIRECTION_PIN, LEFT_ENGINE_SPEED_PIN, RIGHT_ENGINE_DIRECTION_PIN, RIGHT_ENGINE_SPEED_PIN);

Bounce manualModeButton = Bounce();
Bounce calibrationButton = Bounce();
Bounce testButton = Bounce();

ezLED calibrationLed(CALIBRATION_LED_PIN);

State state = State::NORMAL;

Calibrator calibrator = Calibrator({ &arm }, &calibrationLed, onCalibrationFinish)

void setup()
{
    Serial.begin(9600);
    // Ручной режим
    manualModeButton.attach(MANUAL_MODE_BUTTON_PIN);
    manualModeButton.interval(DEBOUNCE_INTERVAL);

    pinMode(MANUAL_MODE_LED_PIN, OUTPUT);

    arm.init();
    platform.init();

    // sizeof(ArmSettings);

    attachInterrupt(digitalPinToInterrupt(LEFT_ENGINE_ENCODER_PIN), readLeftEngineEncoder, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_ENGINE_ENCODER_PIN), readRightEngineEncoder, RISING);

    arm.reset();

    // Калибровка

    calibrationButton.attach(CALIBRATION_BUTTON_PIN);
    calibrationButton.interval(DEBOUNCE_INTERVAL);

    // Тестовое
    testButton.attach(TEST_BUTTON_1_PIN);
    testButton.interval(DEBOUNCE_INTERVAL);
}

void loop()
{
    arm.loop();
    platform.loop();

    buttonsUpdate();

    switch (state)
    {
    case MANUAL:
        manualModeLoop();
        break;
    case CALIBRATION:
        calibrator.loop(analogRead(POT_1_PIN), calibrationButton.fell());
        break;
    case NORMAL:
    default:
        normalLoop();
        break;
    }

    // Тестовое
    if (testButton.fell())
    {
        platform.moveForward(5);
    }
}

void buttonsUpdate()
{
    manualModeButton.update();
    calibrationButton.update();
    testButton.update();
}

void normalLoop()
{
    if (manualModeButton.fell())
    {
        state = State::MANUAL;
        arm.manualModeOn();
        digitalWrite(MANUAL_MODE_LED_PIN, HIGH);
        return;
    }
    if (calibrationButton.fell())
    {
        calibrator.start();
        state = State::CALIBRATION;
        return;
    }
}

void onCalibrationFinish()
{
    state = State::NORMAL;
}

void manualModeLoop()
{
    if (manualModeButton.fell())
    {
        state = State::NORMAL;
        arm.manualModeOff();
        digitalWrite(MANUAL_MODE_LED_PIN, LOW);
        return;
    }

    arm.manualMove(
        map(analogRead(POT_1_PIN), 0, 1023, 0, 180),
        map(analogRead(POT_2_PIN), 0, 1023, 0, 180),
        map(analogRead(POT_3_PIN), 0, 1023, 0, 180),
        map(analogRead(POT_4_PIN), 0, 1023, 0, 180),
        map(analogRead(POT_5_PIN), 0, 1023, 0, 180));
}

void readLeftEngineEncoder()
{
    platform.tickLeft();
}

void readRightEngineEncoder()
{
    platform.tickRight();
}
