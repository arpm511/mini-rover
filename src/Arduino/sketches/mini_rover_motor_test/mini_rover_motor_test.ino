/**
    Control a brushed motor using markerverse motor driver
*/

#define MOTOR_A_PWM_PIN 2
#define MOTOR_A_DIR_PIN 3

byte state = 0;

void setup()
{
    Serial.begin(115200);
    delay(100);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(MOTOR_A_DIR_PIN, OUTPUT);
    pinMode(MOTOR_A_PWM_PIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(MOTOR_A_DIR_PIN, LOW);
    digitalWrite(MOTOR_A_PWM_PIN, HIGH);
}

void loop()
{
    delay(1000);
}