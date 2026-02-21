#include "EventMonitor.hpp"


void EventMonitor::reportSafetyEvent(SafetyLevel level, String message, uint8_t componentId)
{
  SafetyEvent event;
  event.level = level;
  event.componentId = 0; // Default component ID, can be set later
  event.message = message;
  event.timestamp = millis(); // Get the current time in milliseconds

  // Handle the safety event, e.g., log it or send it to a server
  // TODO:

  // For now, we will just print it to the Serial console
  Serial.printf("Safety Event: Level=%d, Message=%s\n", static_cast<int>(level), message.c_str());
  _onSafetyEvent(level, message, componentId);
}

/**
 * @brief Registers a callback for safety events.
 * @param callback The function to call when a critical event occurs.
 * @note This method allows the user to set a callback function that will be invoked when a message is received.
 */
void EventMonitor::onSafetyEvent(SafetyEvtCallback callback)
{
  safetyEvtCallback = callback;
}

/**
 * @brief Registers a callback for message events.
 * @param callback The function to call when a message event occurs.
 * @note This method allows the user to set a callback function that will be invoked when a message is received.
 */
void EventMonitor::onMessage(MessageCallback callback)
{
  messageCallback = callback;
}

/**
 * @brief Registers a callback for message events.
 * @param callback The function to call when a message event occurs.
 * @note This method allows the user to set a callback function that will be invoked when a message is received.
 */
void EventMonitor::onError(ErrorCallback callback)
{
  errorCallback = callback;
}

/**
 * @brief Sends a message event.
 * @param msg The message to send.
 * @note This method is used to send a message event, which will trigger the registered message callback if set.
 */
void EventMonitor::sendMessage(String msg)
{
  _onMessage(msg);
}

/**
 * @brief Sends an error event.
 * @param errorCode The error code associated with the event.
 * @param errorMsg A descriptive message about the error.
 * @note This method is used to send an error event, which will trigger the registered error callback if set.
 */
void EventMonitor::sendError(uint8_t errorCode, String errorMsg)
{
  _onError(errorCode, errorMsg);
}

/**
 * @brief Handles a message event.
 * @param msg The message associated with the event.
 * @note This method is called when a message is received, and it invokes the message callback if set.
 */
void EventMonitor::_onMessage(String msg)
{
  if (messageCallback)
  {
    messageCallback(msg);
  }
}

/**
 * @brief Handles an error event.
 * @param errorCode The error code associated with the event.
 * @param errorMsg A descriptive message about the error.
 * @note This method is called when an error occurs, and it invokes the error callback if set.
 */
void EventMonitor::_onError(uint8_t errorCode, String errorMsg)
{
  if (errorCallback)
  {
    errorCallback(errorCode, errorMsg);
  }
}

/**
 * @brief Handles a system critical event.
 * @param level The safety level of the event.
 * @param msg The message associated with the event.
 * @param componentId The ID of the component that triggered the event.
 * @note This method is called when a safety event occurs, and it invokes the safety event
 */
void EventMonitor::_onSafetyEvent(SafetyLevel level, String message, uint8_t componentId)
{
  if(safetyEvtCallback)
    safetyEvtCallback(level, message, componentId);
}