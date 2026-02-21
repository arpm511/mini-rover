#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H

#include <Arduino.h>
#include "USBHost_t36.h"
#include "EventMonitor.hpp"

/************************************************
 * Defines
 *************************************************/

/* Decode 12-bit signed value (assuming two's complement) */
#define TWELVE_BIT_SIGNED(x) (((x) & 0x800)?(-(((~(x)) & 0xFFF) + 1)):(x))
#define Model_ZCM1 1
//#define Model_ZCM2 0

#define JOY_UPDATE_INTERVAL 50
#define JOY_MSG_INTERVAL 10
#define JOY_REST_POS 127
#define JOY_DEADZONE_THRESHOLD 20
#define JOY_SENSITIVITY 1

typedef void (*JoyCallback)(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry);
typedef void (*ButtonPressCallback)(uint8_t button);

typedef enum {
  JOY = 0,
  X = 1,
  A = 2,
  B = 4,
  Y = 8,
  LB = 16,
  RB = 32,
  LT = 64,
  RT = 128
} JoyButton;

/************************************************
 * Class
 *************************************************/

class JoystickHandler
{
public:
  explicit JoystickHandler(JoystickController &joy_ctrl);
  void begin();
  void update();
  void onJoyMessage(JoyCallback callback);
  void onButtonPress(ButtonPressCallback callback);


private:
  JoystickController &joystick1;
  JoyCallback joyCallback;
  ButtonPressCallback buttonPressCallback;
  bool isPrevDeadzone;
  int joyUpdateInterval;
  int joyMsgInterval;
  int joyRestPos;
  int joyDeadzoneThreshold;
  int joySensitivity;

  unsigned long lastJoyUpdateTime;
  unsigned long lastJoyMsgTime;

  void _onJoyMessage(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry);
  void _onButtonPressMessage(uint8_t button);
};

#endif