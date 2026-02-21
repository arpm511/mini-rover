/**
    Control 6 DC motors and 6 servos
*/
#include "PWMServo.h"

#define MAX_ACTUATORS 6
#define LED_INTERVAL_MS 500
#define STEP 10
#define SERVO_INTERVAL_MS 100

uint8_t motor_pwm_pins[MAX_ACTUATORS] = { 3, 4, 6, 8, 10, 12 };
uint8_t motor_dir_pins[MAX_ACTUATORS] = { 2, 5, 7, 9, 11, 24 };

PWMServo servos[MAX_ACTUATORS];
uint8_t servo_pins[MAX_ACTUATORS] = { 33, 36, 14, 15, 18, 19 };

bool is_sweeping = false;
bool increment = true;
int pos = 0;
byte state = 0;
unsigned long last_time = 0;
unsigned long servo_last_time = 0;
int servo_interval = SERVO_INTERVAL_MS;

void setup()
{
    Serial.begin(115200);
    delay(100);

    pinMode(LED_BUILTIN, OUTPUT);

    for(int i = 0; i < MAX_ACTUATORS; i++)
    {
        pinMode(motor_pwm_pins[i], OUTPUT);
        pinMode(motor_dir_pins[i], OUTPUT);
        servos[i].attach(servo_pins[i]);
    }
}

void position(int angle)
{
    for(int i = 0; i < MAX_ACTUATORS; i++){
        servos[i].write(angle);
    }

    Serial.print("angle: ");
    Serial.println(angle);
}

void sweep()
{
    unsigned long now = millis();

    if(now - servo_last_time > servo_interval)
    {
        servo_last_time = now;

        if(pos >= 180)
            increment = false;

        if(pos <= 0)
            increment = true;

        pos = increment ? pos + STEP :  pos - STEP;
        
        position(pos);
    }
}

void move()
{
    for(int i = 0; i < MAX_ACTUATORS; i++)
    {
        digitalWrite(motor_pwm_pins[i], HIGH);
        digitalWrite(motor_dir_pins[i], HIGH);

        delay(100);
    }
}

void move(int wheel)
{
    int idx = wheel - 1;
    
    digitalWrite(motor_pwm_pins[idx], HIGH);
    digitalWrite(motor_dir_pins[idx], HIGH);
}

void stop()
{
    for(int i = 0; i < MAX_ACTUATORS; i++)
    {
        digitalWrite(motor_pwm_pins[i], LOW);
        digitalWrite(motor_dir_pins[i], LOW);
    }

    is_sweeping = false;
}

void loop()
{
    if(Serial.available())
    {
        const char c = Serial.read();

        switch(c){
            case 's':
                is_sweeping = true;
                break;

            case 'a':
                is_sweeping = false;
                position(180);
                break;

            case 'w':
                is_sweeping = false;
                position(90);
                break;

            case 'd':
                is_sweeping = false;
                position(0);
                break;

            case 'e':
                move();
                break;

            case 'q':
                stop();
                break;

            case '=':
                servo_interval += 10;
                if(servo_interval > 500)
                    servo_interval = 500;
                Serial.print("Servo interval: "); Serial.println(servo_interval);
                break;

            case '-':
                servo_interval -= 10;
                if(servo_interval < 10)
                    servo_interval = 10;
                Serial.print("Servo interval: "); Serial.println(servo_interval);
                break;

            case '1':
                move(1);
                break;

            case '2':
                move(2);
                break;

            case '3':
                move(3);
                break;

            case '4':
                move(4);
                break;

            case '5':
                move(5);
                break;
            
            case '6':
                move(6);
                break;

            default:
                break;
        }
    }

    if(is_sweeping)
        sweep();

    unsigned long now = millis();

    if(now - last_time > LED_INTERVAL_MS){
        last_time = now;
        state = !state;
        digitalWrite(LED_BUILTIN, state);
    }
}