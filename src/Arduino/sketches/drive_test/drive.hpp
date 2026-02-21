#ifndef DRIVE_H
#define DRIVE_H

#define MOTORS_DELAY_MS 100
#define SERVOS_DELAY_MS 80

class Drive
{
    public:
        static Drive &getInstance()
        {
            static Drive instance;
            return instance;
        }

        void begin();
        void update();
        void move(float lx, float ly, float rx, float ry);

    private:
        Drive();
        Drive(const Drive&) = delete;
        Drive& operator=(const Drive&) = delete;

        unsigned long time_since_last_motor_move = 0;
        unsigned long time_since_last_servo_move = 0;

        void moveMotors(float inp);
        void moveServos(float inp);
};

#endif