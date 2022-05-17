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

#define MANUAL_MODE_BUTTON_PIN 35 // B1
#define CALIBRATION_BUTTON_PIN 34 // B2
#define TEST_BUTTON_1_PIN 31      // B5
#define TEST_BUTTON_2_PIN 30      // B6

// Светодиоды

#define MANUAL_MODE_LED_PIN 22    // LED1
#define CALIBRATION_LED_PIN 23    // LED2

// Состояния

enum State {
    NORMAL,
    MANUAL,
    CALIBRATION
};
