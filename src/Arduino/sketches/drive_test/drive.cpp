#include "drive.hpp"
#include "servo_controller.hpp"
#include "motor_controller.hpp"
#include "common.h"

Drive::Drive(){}

void Drive::begin()
{
    ServoController::getInstance().begin();
    MotorController::getInstance().begin();
}

void Drive::update()
{
    ServoController::getInstance().update();
    MotorController::getInstance().update();
}

void Drive::move(float lx, float ly, float rx, float ry)
{
    moveMotors(ly);
    moveServos(rx);
}

void Drive::moveMotors(float inp)
{
    unsigned long now = millis();

    if(now - time_since_last_motor_move > MOTORS_DELAY_MS)
    {
        time_since_last_motor_move = now;

        if(inp > 0.0f && inp < 1.0f)
        {
            if(inp < 0.4f){
                Serial.println("STOP");
                MotorController::getInstance().stop();
            }
            else{
                float s = map(inp, 0.0f, 1.0f, 0.0f, 255.0f);

                int speed = static_cast<int>(s);
                Serial.print("SPEED: ");
                Serial.println(speed);
                MotorController::getInstance().move(speed);
            }
        }
    }
}

void Drive::moveServos(float inp)
{
    unsigned now = millis();

    if(now - time_since_last_servo_move > SERVOS_DELAY_MS)
    {
        time_since_last_servo_move = now;

        float a = map(inp, -1.0f, 1.0f, 0.0f, 180.0f);
        int angle = static_cast<int>(a);

        Serial.print("ANGLE: ");
        Serial.println(angle);
        ServoController::getInstance().move(angle);
    }
}