/**
    Control a brushed motor using markerverse motor driver
*/

#define MOTOR_FRONT_A_DIR_PIN 2
#define MOTOR_FRONT_A_PWM_PIN 3
#define MOTOR_FRONT_B_PWM_PIN 4
#define MOTOR_FRONT_B_DIR_PIN 5
#define MOTOR_MIDDLE_A_PWM_PIN 6
#define MOTOR_MIDDLE_A_DIR_PIN 7
#define MOTOR_MIDDLE_B_PWM_PIN 8
#define MOTOR_MIDDLE_B_DIR_PIN 9
#define MOTOR_REAR_A_PWM_PIN 10
#define MOTOR_REAR_A_DIR_PIN 11
#define MOTOR_REAR_B_PWM_PIN 12
#define MOTOR_REAR_B_DIR_PIN 24

byte state = 0;

void setup()
{
    Serial.begin(115200);
    delay(100);

    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(MOTOR_FRONT_A_DIR_PIN, OUTPUT);
    pinMode(MOTOR_FRONT_A_PWM_PIN, OUTPUT);
    pinMode(MOTOR_FRONT_B_DIR_PIN, OUTPUT);
    pinMode(MOTOR_FRONT_B_PWM_PIN, OUTPUT);

    pinMode(MOTOR_MIDDLE_A_DIR_PIN, OUTPUT);
    pinMode(MOTOR_MIDDLE_A_PWM_PIN, OUTPUT);
    pinMode(MOTOR_MIDDLE_B_DIR_PIN, OUTPUT);
    pinMode(MOTOR_MIDDLE_B_PWM_PIN, OUTPUT);

    pinMode(MOTOR_REAR_A_DIR_PIN, OUTPUT);
    pinMode(MOTOR_REAR_A_PWM_PIN, OUTPUT);
    pinMode(MOTOR_REAR_B_DIR_PIN, OUTPUT);
    pinMode(MOTOR_REAR_B_PWM_PIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
}

void move()
{
    digitalWrite(MOTOR_FRONT_A_DIR_PIN, HIGH);
    digitalWrite(MOTOR_FRONT_A_PWM_PIN, HIGH);
    digitalWrite(MOTOR_FRONT_B_DIR_PIN, HIGH);
    digitalWrite(MOTOR_FRONT_B_PWM_PIN, HIGH);

    digitalWrite(MOTOR_MIDDLE_A_DIR_PIN, HIGH);
    digitalWrite(MOTOR_MIDDLE_A_PWM_PIN, HIGH);
    digitalWrite(MOTOR_MIDDLE_B_DIR_PIN, HIGH);
    digitalWrite(MOTOR_MIDDLE_B_PWM_PIN, HIGH);

    digitalWrite(MOTOR_REAR_A_DIR_PIN, HIGH);
    digitalWrite(MOTOR_REAR_A_PWM_PIN, HIGH);
    digitalWrite(MOTOR_REAR_B_DIR_PIN, HIGH);
    digitalWrite(MOTOR_REAR_B_PWM_PIN, HIGH);
}

void loop()
{
    move();
}