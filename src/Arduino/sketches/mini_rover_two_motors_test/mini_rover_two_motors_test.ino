/**
    Control a brushed motor using markerverse motor driver
*/

#define MOTOR_A_PWM_PIN 3
#define MOTOR_A_DIR_PIN 2
#define MOTOR_B_PWM_PIN 4
#define MOTOR_B_DIR_PIN 5

byte state = 0;

void setup()
{
    Serial.begin(115200);
    delay(100);

    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(MOTOR_A_DIR_PIN, OUTPUT);
    pinMode(MOTOR_A_PWM_PIN, OUTPUT);

    pinMode(MOTOR_B_DIR_PIN, OUTPUT);
    pinMode(MOTOR_B_PWM_PIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
}

void moveA()
{
    digitalWrite(MOTOR_B_DIR_PIN, LOW);
    digitalWrite(MOTOR_B_PWM_PIN, LOW);

    delay(500);

    digitalWrite(MOTOR_A_DIR_PIN, LOW);
    digitalWrite(MOTOR_A_PWM_PIN, HIGH);
}

void moveB()
{
    digitalWrite(MOTOR_A_DIR_PIN, LOW);
    digitalWrite(MOTOR_A_PWM_PIN, LOW);

    delay(500);

    digitalWrite(MOTOR_B_DIR_PIN, LOW);
    digitalWrite(MOTOR_B_PWM_PIN, HIGH);
}

void moveBoth()
{
    digitalWrite(MOTOR_A_DIR_PIN, LOW);
    digitalWrite(MOTOR_A_PWM_PIN, HIGH);

    digitalWrite(MOTOR_B_DIR_PIN, LOW);
    digitalWrite(MOTOR_B_PWM_PIN, HIGH);
}

void loop()
{
    if(Serial.available())
    {
        const char c = Serial.read();

        Serial.print("Pressed ");
        Serial.println(c);

        switch(c)
        {
            case '1':
                moveA();
                break;

            case '2':
                moveB();
                break;

            case '3':
                moveBoth();
                break;

            default:
                break;
        }
    }
}