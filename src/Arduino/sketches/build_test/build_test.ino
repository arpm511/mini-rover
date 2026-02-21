/**
    Control 6 DC motors and 6 servos
*/

#include "common.h"
#include "servo_controller.hpp"
#include "motor_controller.hpp"

#define LED_INTERVAL_MS 1000

byte led_state = 0;
unsigned long time_since_led = 0;
int mode = 1;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

    ServoController::getInstance().begin();
    MotorController::getInstance().begin();
}

void loop()
{
    unsigned long now = millis();
    if(now - time_since_led > LED_INTERVAL_MS){
        time_since_led = now;
        led_state = !led_state;
        digitalWrite(LED_BUILTIN, led_state);
    }


    if(Serial.available())
    {
        const char c = Serial.read();

        switch(c)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                if(mode == 0)
                    ServoController::getInstance().sweeping_single = c - '0';

                if(mode == 1)
                    MotorController::getInstance().move(c - '0');
                break;

            case 's':
                if(mode == 0)
                {
                    ServoController::getInstance().sweeping_single = -1;
                    ServoController::getInstance().is_sweeping = true;
                }

                if(mode == 1)
                    MotorController::getInstance().move();
                break;

            case 'a':
                ServoController::getInstance().move(0);
                break;

            case 'w':
                ServoController::getInstance().move(90);
                break;

            case 'd':
                ServoController::getInstance().move(180);
                break;

            case 'm':
                mode = mode == 0 : 1 : 0;
                break;

            case 'q':
                ServoController::getInstance().sweeping_single = -1;
                ServoController::getInstance().is_sweeping = false;

                MotorController::getInstance().stop();
                break;

            default:
                break;
        }
    }

    ServoController::getInstance().update();
    MotorController::getInstance().update();
}