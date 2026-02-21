#include "Arduino.h"
#include "servo_controller.hpp"

ServoController::ServoController(){}

void ServoController::begin()
{
    registerServo(23, REAR_RIGHT);
    registerServo(22, MIDDLE_RIGHT);
    registerServo(19, FRONT_RIGHT); // FAULTY??
    registerServo(18, FRONT_LEFT);
    registerServo(15, MIDDLE_LEFT);
    registerServo(14, REAR_LEFT); // FAULTY??
}

void ServoController::update()
{
    if(sweeping_single != -1)
    {
        sweep(sweeping_single);
        return;
    }

   if(is_sweeping)
   {
        sweep();
        return;
   }
}

void ServoController::registerServo(int pin, Slot slot)
{
    pinMode(pin, OUTPUT);

    int idx = static_cast<int>(slot);

    servos[idx].pin = pin;
    servos[idx].slot = slot;
    servos[idx].ctrl.attach(pin);
}

void ServoController::sweep(Slot slot)
{
    unsigned long now = millis();

    if(now - servo_last_time > SERVO_INTERVAL_MS)
    {
        servo_last_time = now;

        if(pos >= 180)
            increment = false;

        if(pos <= 0)
            increment = true;

        pos = increment ? pos + STEP :  pos - STEP;
        
        int i = static_cast<int>(slot);
        servos[i].ctrl.write(pos);

        Serial.print("angle: ");
        Serial.println(pos);
    }
}

void ServoController::sweep(int idx)
{
    unsigned long now = millis();

    if(now - servo_last_time > SERVO_INTERVAL_MS)
    {
        servo_last_time = now;

        if(pos >= 180)
            increment = false;

        if(pos <= 0)
            increment = true;

        pos = increment ? pos + STEP :  pos - STEP;
        
        servos[idx].ctrl.write(pos);

        Serial.print("angle: ");
        Serial.println(pos);
    }
}

void ServoController::sweep()
{
    unsigned long now = millis();

    if(now - servo_last_time > SERVO_INTERVAL_MS)
    {
        servo_last_time = now;

        if(pos >= 180)
            increment = false;

        if(pos <= 0)
            increment = true;

        pos = increment ? pos + STEP :  pos - STEP;
        
        for(int i = 0; i < MAX_ACTUATORS; i++){
            servos[i].ctrl.write(pos);
        }

        Serial.print("angle: ");
        Serial.println(pos);
    }
}

void ServoController::move(int idx, int pos)
{
    int angle = pos;
    if(angle < 0)
        angle = 0;

    if(angle > 180)
        angle = 180;

    servos[idx].ctrl.write(angle);
}

void ServoController::move(Slot slot, int pos)
{
    int idx = static_cast<int>(slot);

    move(idx, pos);
}

void ServoController::move(int pos)
{
    for(int i = 0; i < MAX_ACTUATORS; i++)
    {
        move(i, pos);
    }
}