
#include "motor_controller.hpp"

MotorController::MotorController(){}

void MotorController::begin()
{
    registerMotor(2, 3, MIDDLE_LEFT, Direction::CLOCKWISE);
    registerMotor(4, 5, MIDDLE_RIGHT, Direction::CLOCKWISE);

    registerMotor(6, 7, REAR_RIGHT, Direction::CLOCKWISE);
    registerMotor(8, 9, REAR_LEFT, Direction::ANTICLOCKWISE);

    registerMotor(10, 11, FRONT_RIGHT, Direction::CLOCKWISE);
    registerMotor(24, 25, FRONT_LEFT, Direction::ANTICLOCKWISE);
}

void MotorController::update()
{

}

void MotorController::registerMotor(int pwmPin, int dirPin, Slot slot, Direction dir)
{
    pinMode(pwmPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    int idx = static_cast<int>(slot);
    motors[idx].pwmPin = pwmPin;
    motors[idx].dirPin = dirPin;
    motors[idx].slot = slot;
    motors[idx].dir = dir;
}

void MotorController::move(int idx, int speed)
{
    int dir = motors[idx].dir == Direction::CLOCKWISE ? HIGH : LOW;
    
    if(speed < 0)
        speed = 0;

    if(speed > 255)
        speed = 255;

    digitalWrite(motors[idx].dirPin, dir);
    digitalWrite(motors[idx].pwmPin, HIGH);
}

void MotorController::move(Slot slot, int speed)
{
    int idx = static_cast<int>(slot);
    move(idx, speed);
}

void MotorController::move(int speed)
{
    for(int i = 0; i < MAX_ACTUATORS; i++){
        move(i, speed);
    }
}

void MotorController::stop()
{
    for(int i = 0; i < MAX_ACTUATORS; i++)
    {
        digitalWrite(motors[i].dirPin, LOW);
        digitalWrite(motors[i].pwmPin, LOW);
    }
}