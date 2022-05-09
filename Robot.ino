#include <Bounce2.h>
#include "Arm.h"
#include "Platform.h"

// Двигатели

#define LEFT_ENGINE_DIRECTION_PIN 47
#define LEFT_ENGINE_SPEED_PIN 46
#define LEFT_ENGINE_ENCODER_PIN 2

#define RIGHT_ENGINE_DIRECTION_PIN 45
#define RIGHT_ENGINE_SPEED_PIN 44
#define RIGHT_ENGINE_ENCODER_PIN 3

// Сервоприводы

#define ARM_ROTATION_SERVO_PIN 5
#define ARM_LIFT_SERVO_PIN 6
#define CLAW_LIFT_SERVO_PIN 7
#define CLAW_ROTATION_SERVO_PIN 8
#define CLAW_SERVO_PIN 9

// Потенциометры

#define POT_1_PIN A10
#define POT_2_PIN A11
#define POT_3_PIN A12
#define POT_4_PIN A13
#define POT_5_PIN A14
#define POT_6_PIN A15

// Кнопки

#define DEBOUNCE_INTERVAL 5

#define MANUAL_MODE_BUTTON_PIN 35   // B1
#define TEST_BUTTON_1_PIN 31        // B5
#define TEST_BUTTON_2_PIN 30        // B6

// Светодиоды

#define MANUAL_MODE_LED_PIN 22 // LED1
#define CALIBRATION_LED_PIN 23 // LED2

Arm arm;
Platform platform;

Bounce manualModeButton = Bounce();
Bounce testButton = Bounce();

void setup()
{
    Serial.begin(9600);
    // Ручной режим
    manualModeButton.attach(MANUAL_MODE_BUTTON_PIN);
    manualModeButton.interval(DEBOUNCE_INTERVAL);

    pinMode(MANUAL_MODE_LED_PIN, OUTPUT);

    // arm.init(ARM_ROTATION_SERVO_PIN, ARM_LIFT_SERVO_PIN, CLAW_LIFT_SERVO_PIN, CLAW_ROTATION_SERVO_PIN, CLAW_SERVO_PIN);
    platform.init(LEFT_ENGINE_DIRECTION_PIN, LEFT_ENGINE_SPEED_PIN, RIGHT_ENGINE_DIRECTION_PIN, RIGHT_ENGINE_SPEED_PIN);

    attachInterrupt(digitalPinToInterrupt(LEFT_ENGINE_ENCODER_PIN), readLeftEngineEncoder, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_ENGINE_ENCODER_PIN), readRightEngineEncoder, RISING);

    arm.reset();
    
    // Тестовое
    testButton.attach(TEST_BUTTON_1_PIN);
    testButton.interval(DEBOUNCE_INTERVAL);
}

void loop()
{
//     digitalWrite(LEFT_ENGINE_DIRECTION_PIN, LOW);
//     analogWrite(LEFT_ENGINE_SPEED_PIN, 150);
    // Serial.print(countLeft);
    // Serial.print(" ");
    // Serial.print(countRight);
    // Serial.println();

    // arm.manualMove(
    //     map(analogRead(POT_1_PIN), 0, 1023, 0, 180),
    //     map(analogRead(POT_2_PIN), 0, 1023, 0, 180),
    //     map(analogRead(POT_3_PIN), 0, 1023, 0, 180),
    //     map(analogRead(POT_4_PIN), 0, 1023, 0, 180),
    //     map(analogRead(POT_5_PIN), 0, 1023, 0, 180));

    arm.loop();
    platform.loop();

    // Ручной режим
    manualModeButton.update();
    if (manualModeButton.fell())
    {
        if (arm.isManual())
        {
            arm.manualModeOff();
            digitalWrite(MANUAL_MODE_LED_PIN, LOW);
        }
        else
        {
            arm.manualModeOn();
            digitalWrite(MANUAL_MODE_LED_PIN, HIGH);
        }
    }
    // Тестовое
    testButton.update();
    if (testButton.fell()) {
        platform.moveForward(5);
    }
}

void readLeftEngineEncoder()
{
    platform.tickLeft();
}

void readRightEngineEncoder()
{
    platform.tickRight();
}
