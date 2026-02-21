#include "JoystickHandler.hpp"

bool firstJoystickMessage = true;

/**
 * @brief Initializes the JoystickHandler with a reference to a JoystickController.
 * @param joy_ctrl Reference to the JoystickController object.
 */
JoystickHandler::JoystickHandler(JoystickController &joy_ctrl) :
  joystick1(joy_ctrl), joyCallback(nullptr), buttonPressCallback(nullptr){ }

/**
 * @brief Initializes the JoystickHandler. This function should be called in the setup() function of the main program.
 */
void JoystickHandler::begin()
{
  EventMonitor::getInstance().sendMessage("JoystickHandler initialized.");
}

/**
 * @brief Updates the joystick state and processes input.
 */
void JoystickHandler::update()
{
  if(joystick1.available())
  {
    if(firstJoystickMessage)
    {
      firstJoystickMessage = false;
      EventMonitor::getInstance().sendMessage("*** First Joystick message " + String(joystick1.idVendor(), HEX) + ":" + String(joystick1.idProduct(), HEX) + " ***" + String("  manufacturer: ") + (const char *)joystick1.manufacturer() + String("  product: ") + (const char *)joystick1.product() + String("  Serial: ") + (const char *)joystick1.serialNumber());
      joystick1.axisChangeNotifyMask(0xFFFFFl);
      return;
    }
    
    // Process joystick data

    uint8_t lx = joystick1.getAxis(0);
    uint8_t ly = joystick1.getAxis(1);
    uint8_t rx = joystick1.getAxis(2);
    uint8_t ry = joystick1.getAxis(5);

    // Check for button presses
    uint32_t buttons = joystick1.getButtons();

    unsigned now = millis();

    if(now - lastJoyMsgTime > JOY_MSG_INTERVAL)
    {
      // Notify if a callback is set
      if(joyCallback)
        joyCallback(lx, ly, rx, ry);

      if(buttons && buttonPressCallback)
        buttonPressCallback(buttons);
    }

    if(now - lastJoyUpdateTime > JOY_UPDATE_INTERVAL){
      lastJoyUpdateTime = now;
      joystick1.joystickDataClear();
      joystick1.axisChangeNotifyMask(0xFFFFFl);
    }
  }
}

/**
 * @brief Sets the callback function for messages.
 * @param callback Callback function to be called on joystick messages.
 */
void JoystickHandler::onJoyMessage(JoyCallback callback)
{
  joyCallback = callback;
}

/**
 * @brief Callback function for joystick messages.
 * @param lx Left joystick X value.
 * @param ly Left joystick Y value.
 * @param rx Right joystick X value.
 * @param ry Right joystick Y value.
 */
void JoystickHandler::_onJoyMessage(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry)
{
  if (joyCallback != nullptr)
    joyCallback(lx, ly, rx, ry);
}

/**
 * @brief Sets the callback function for button press events.
 * @param callback Callback function to be called on button press.
 */
void JoystickHandler::onButtonPress(ButtonPressCallback callback)
{
  buttonPressCallback = callback;
}

/**
 * @brief Callback function for button press messages.
 * @param button Button index that was pressed.
 */
void JoystickHandler::_onButtonPressMessage(uint8_t button)
{
  if (buttonPressCallback)
    buttonPressCallback(button);
}