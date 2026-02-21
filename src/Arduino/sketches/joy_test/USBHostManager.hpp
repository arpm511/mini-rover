#ifndef USBHOSTMANAGER_H
#define USBHOSTMANAGER_H

#include "Arduino.h"
#include "USBHost_t36.h"
#include "EventMonitor.hpp"

/************************************************
 * Defines
 *************************************************/

#define CNT_DEVICES 3
#define CNT_HIDDEVICES 1

/************************************************
 * Class
 *************************************************/

class USBHostManager
{
public:
  explicit USBHostManager(USBHost &usbHost, JoystickController &joy_ctrl);
  void begin();
  void update();

private:
  USBHost &hostusb;
  JoystickController &joystick1;
  USBHub hub1;
  USBHIDParser hid1;

  USBDriver *drivers[CNT_DEVICES];
  USBHIDInput *hiddrivers[CNT_HIDDEVICES];
  const char *driver_names[CNT_DEVICES];
  const char *hid_driver_names[CNT_HIDDEVICES];

  void updateDeviceInfo();
};

#endif
