#include "USBHost_t36.h"
#include "USBHostManager.hpp"
#include "JoystickHandler.hpp"
#include "EventMonitor.hpp"
#include "drive.hpp"
#include "common.h"

#define LED_INTERVAL_MS 1000

USBHost usbhost;
JoystickController joystick1(usbhost);
USBHostManager usbHostManager(usbhost, joystick1);
JoystickHandler joystickHandler(joystick1);

byte led_state = 0;
unsigned long last_led_time = 0;

int x1_input = 0;
int y1_input = 0;
int x2_input = 0;
int y2_input = 0;

void scheduleMovement()
{
    // Normalize between -1 and 1

    float lxn = ((float)x1_input / 255.0f) * 2.0f - 1.0f;
    float lyn = ((float)y1_input / 255.0f) * 2.0f - 1.0f;
    float rxn = ((float)x2_input / 255.0f) * 2.0f - 1.0f;
    float ryn = ((float)y2_input / 255.0f) * 2.0f - 1.0f;

    lyn = lyn * -1.0f;

    Drive::getInstance().move(lxn, lyn, rxn, ryn);
}

void handleJoyMovement(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry)
{
    //Serial.println("Joystick Message Received | LX: " + String(lx) + ", LY: " + String(ly) + ", RX: " + String(rx) + ", RY: " + String(ry));

    x1_input = lx;
    y1_input = ly;
    x2_input = rx;
    y2_input = ry;

    scheduleMovement();
}

void handleJoyPress(uint8_t button)
{
  Serial.println("Joystick Button Pressed: " + String(button));
}

void handleMessage(String msg)
{
  Serial.println(msg);
}

void handleError(uint8_t errorCode, String errorMsg)
{
  Serial.print("Error ");
  Serial.print(errorCode);
  Serial.print(" : ");
  Serial.println(errorMsg);
}

void setup()
{
    SCB_SHCSR |= SCB_SHCSR_MEMFAULTENA;
    Serial1.begin(2000000);
    Serial.begin(115200);
    
    //while (!Serial); // wait for Arduino Serial Monitor
    delay(500);

    if (CrashReport)
        Serial.print(CrashReport);

    EventMonitor::getInstance().onMessage(handleMessage);
    EventMonitor::getInstance().onError(handleError);

    pinMode(LED_BUILTIN, OUTPUT);

    usbHostManager.begin();
    joystickHandler.onJoyMessage(handleJoyMovement);
    joystickHandler.onButtonPress(handleJoyPress);
    joystickHandler.begin();

    Drive::getInstance().begin();
}

void loop()
{
    unsigned long now = millis();

    if(now - last_led_time > LED_INTERVAL_MS)
    {
        last_led_time = now;
        led_state = !led_state;

        digitalWrite(LED_BUILTIN, led_state);
    }

    usbHostManager.update();
    joystickHandler.update();

    Drive::getInstance().update();
}