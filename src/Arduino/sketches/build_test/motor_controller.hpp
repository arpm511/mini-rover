#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "Arduino.h"
#include "common.h"

typedef enum {
    CLOCKWISE,
    ANTICLOCKWISE
} Direction;

typedef struct {
    int pwmPin;
    int dirPin;
    Slot slot;
    Direction dir;
} MyMotor;

class MotorController
{
    public:
        static MotorController &getInstance()
        {
            static MotorController instance;
            return instance;
        }

        void begin();
        void update();
        void registerMotor(int pwmPin, int dirPin, Slot slot, Direction dir);

        void move();
        void move(int idx);
        void move(Slot slot);
        void stop();

    private:
        MotorController();
        MotorController(const MotorController&) = delete;
        MotorController& operator=(const MotorController&) = delete;

        MyMotor motors[MAX_ACTUATORS];
};

#endif