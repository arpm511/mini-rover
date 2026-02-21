#include "USBHostManager.hpp"
#include <stdio.h>

bool driver_active[CNT_DEVICES] = { false, false, false };
bool hid_driver_active[CNT_HIDDEVICES] = { false };

/**
 * Constructor
 * @brief This constructor initializes the USBHostManager and its components.
 * @param usbHost The USBHost object to be used.
 * @param joy_ctrl The JoystickController object to be used.
 */
USBHostManager::USBHostManager(USBHost &usbHost, JoystickController &joy_ctrl) : 
hostusb(usbHost), joystick1(joy_ctrl), hub1(usbHost), hid1(usbHost)
{
  drivers[0] = &hub1;
  drivers[1] = &joystick1;
  drivers[2] = &hid1;

  driver_names[0] = "Hub1";
  driver_names[1] = "JOY1D";
  driver_names[2] = "HID1";

  hiddrivers[0] = &joystick1;
  hid_driver_names[0] = "Joystick1";
}

 /**
  * @brief Initializes the USBHostManager and its components.
  * @details This function initializes the USBHostManager, starts the USB host, and sends
  */
void USBHostManager::begin()
{
  hostusb.begin();
  EventMonitor::getInstance().sendMessage("USBHostManager initialized.");
}

 /**
  * @brief Updates the device information.
  * @details This function checks for available USB devices and processes them.
  */
void USBHostManager::updateDeviceInfo()
{
  char buffer[128]; // Static buffer for messages
  
  for (uint8_t i = 0; i < CNT_DEVICES; i++) 
  {
    if(drivers[i] == nullptr)
      continue;

    if (*drivers[i] != driver_active[i]) {
      if (driver_active[i]) 
      {
        snprintf(buffer, sizeof(buffer), "*** Device %s - disconnected***", driver_names[i]);
        EventMonitor::getInstance().sendMessage(buffer);
        driver_active[i] = false;
      } 
      else
      {
        snprintf(buffer, sizeof(buffer), "*** Device %s %x:%x - connected ***", 
                driver_names[i], drivers[i]->idVendor(), drivers[i]->idProduct());
        EventMonitor::getInstance().sendMessage(buffer);
        driver_active[i] = true;
      }
    }
  }

  for (uint8_t i = 0; i < CNT_HIDDEVICES; i++)
  {
    if(hiddrivers[i] == nullptr) 
      continue;

    if (*hiddrivers[i] != hid_driver_active[i])
    {
      if (hid_driver_active[i])
      {
        snprintf(buffer, sizeof(buffer), "*** Device %s - disconnected***", hid_driver_names[i]);
        EventMonitor::getInstance().sendMessage(buffer);
        hid_driver_active[i] = false;
      }
      else
      {
        snprintf(buffer, sizeof(buffer), "*** HID Device %s %x:%x - connected ***", 
                hid_driver_names[i], hiddrivers[i]->idVendor(), hiddrivers[i]->idProduct());
        EventMonitor::getInstance().sendMessage(buffer);
        hid_driver_active[i] = true;

        const uint8_t *psz = hiddrivers[i]->manufacturer();
        if (psz && *psz)
          EventMonitor::getInstance().sendMessage("  manufacturer: " + String((const char *)psz));

        psz = hiddrivers[i]->product();
        if (psz && *psz)
          EventMonitor::getInstance().sendMessage("  product: " + String((const char *)psz));

        psz = hiddrivers[i]->serialNumber();
        if (psz && *psz)
          EventMonitor::getInstance().sendMessage("  Serial: " + String((const char *)psz));

        // See if this is our joystick object...
        if (hiddrivers[i] == &joystick1)
          EventMonitor::getInstance().sendMessage("  Joystick type: " + String(joystick1.joystickType()));
      }
    }
  }
}

/**
 * @brief Updates the USB host manager.
 * @details This function calls the USB host task and updates the device information.
 */
void USBHostManager::update()
{
  hostusb.Task();
  updateDeviceInfo();
}