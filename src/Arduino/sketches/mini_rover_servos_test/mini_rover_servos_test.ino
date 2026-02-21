#include "PWMServo.h"

#define MAX_SERVOS 6
#define LED_INTERVAL_MS 500
#define STEP 10

PWMServo servos[MAX_SERVOS];
uint8_t servo_pins[MAX_SERVOS] = { 2, 3, 4, 5, 6, 7 };

bool is_sweeping = false;
bool increment = true;
int pos = 0;

unsigned long last_time = 0;
byte state = 0;

void setup()
{
    Serial.begin(115200);
    delay(100);

    pinMode(LED_BUILTIN, OUTPUT);

    for(int i = 0; i < MAX_SERVOS; i++){
        servos[i].attach(servo_pins[i]);
    }
}

void sweep()
{
    if(pos >= 180)
        increment = false;

    if(pos <= 0)
        increment = true;

    pos = increment ? pos + STEP :  pos - STEP;
    
    position(pos);
}

void position(int angle)
{
    for(int i = 0; i < MAX_SERVOS; i++){
        servos[i].write(angle);
        delay(10);
    }

    Serial.print("angle: ");
    Serial.println(angle);
}

// 180 == left
// 90 == center
// 0 == right
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