#include "Arm.h"
// #include <HardwareSerial.h>

// ДВИГАТЕЛИ

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

// Кнопки

#define MANUAL_MODE_BUTTON_PIN 35 // B1

// Светодиоды

#define MANUAL_MODE_LED_PIN 22 // LED1

Arm arm;
bool manualModeButtonLastState = LOW;
bool manualModeButtonCurrentState = LOW;

volatile int countLeft = 0;
volatile int countRight = 0;

void setup()
{
    Serial.begin(9600);
    // Ручной режим
    pinMode(MANUAL_MODE_BUTTON_PIN, INPUT);
    pinMode(MANUAL_MODE_LED_PIN, OUTPUT);

    //  pinMode(LEFT_ENGINE_ENCODER_PIN, INPUT);
    //  pinMode(RIGHT_ENGINE_ENCODER_PIN, INPUT);
    //  attachInterrupt(digitalPinToInterrupt(LEFT_ENGINE_ENCODER_PIN), readLeftEngineEncoder, RISING);
    //  attachInterrupt(digitalPinToInterrupt(RIGHT_ENGINE_ENCODER_PIN), readRightEngineEncoder, RISING);
    // pinMode(LEFT_ENGINE_DIRECTION_PIN, OUTPUT);
    // pinMode(LEFT_ENGINE_SPEED_PIN, OUTPUT);
    //
    // pinMode(RIGHT_ENGINE_DIRECTION_PIN, OUTPUT);
    // pinMode(RIGHT_ENGINE_SPEED_PIN, OUTPUT);
    //
    // digitalWrite(LEFT_ENGINE_DIRECTION_PIN, LOW);
    // analogWrite(LEFT_ENGINE_SPEED_PIN, 150);
    // digitalWrite(RIGHT_ENGINE_DIRECTION_PIN, LOW);
    // analogWrite(RIGHT_ENGINE_SPEED_PIN, 150);
    arm.init(ARM_ROTATION_SERVO_PIN, ARM_LIFT_SERVO_PIN, CLAW_LIFT_SERVO_PIN, CLAW_ROTATION_SERVO_PIN, CLAW_SERVO_PIN);

    arm.moveTo(90, 90, 90, 90, 90, 3000);
}

void loop()
{
    // Serial.print(countLeft);
    // Serial.print(" ");
    // Serial.print(countRight);
    // Serial.println();

    arm.manualMove(
        map(analogRead(POT_1_PIN), 0, 1023, 10, 170),
        map(analogRead(POT_2_PIN), 0, 1023, 10, 170),
        map(analogRead(POT_3_PIN), 0, 1023, 10, 170),
        map(analogRead(POT_4_PIN), 0, 1023, 10, 170),
        map(analogRead(POT_5_PIN), 0, 1023, 10, 170)
    );

    arm.loop();

    // Ручной режим
    manualModeButtonCurrentState = digitalRead(MANUAL_MODE_BUTTON_PIN);
    if (manualModeButtonLastState == LOW && manualModeButtonCurrentState == HIGH)
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
    manualModeButtonLastState = manualModeButtonCurrentState;
}

void readLeftEngineEncoder()
{
    countLeft++;
}

void readRightEngineEncoder()
{
    countRight++;
}
