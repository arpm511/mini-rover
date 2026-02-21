#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include "Arduino.h"
#include "PWMServo.h"
#include "common.h"

#define STEP 10
#define SERVO_INTERVAL_MS 100

typedef struct {
    int pin;
    Slot slot;
    PWMServo ctrl;
    int pos;
} MyServo;

class ServoController
{
    public:
        MyServo servos[MAX_ACTUATORS];

        static ServoController &getInstance()
        {
            static ServoController instance;
            return instance;
        }

        bool is_sweeping = false;
        int sweeping_single = -1;

        void begin();
        void update();
        void registerServo(int pin, Slot slot);
        void move(Slot slot, int angle);
        void move(int slot, int angle);
        void move(int angle);

    private:
        ServoController();
        ServoController(const ServoController&) = delete;
        ServoController& operator=(const ServoController&) = delete;

        int pos = 0;
        unsigned long servo_last_time = 0;
        bool increment = false;

        void sweep(Slot slot);
        void sweep(int idx);
        void sweep();
};

#endif // SERVO_CONTROLLER_H