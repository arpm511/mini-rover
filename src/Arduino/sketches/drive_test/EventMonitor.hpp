#ifndef EVENT_MONITOR_H
#define EVENT_MONITOR_H

#include <Arduino.h>

/************************************************
 * Defines
 *************************************************/

enum class SafetyLevel
{
    INFO,
    WARNING,
    CRITICAL,
    EMERGENCY
};

struct SafetyEvent
{
    SafetyLevel level;
    uint8_t componentId;
    String message;
    unsigned long timestamp;
};

typedef void (*MessageCallback)(String);
typedef void (*ErrorCallback)(uint8_t, String);
typedef void (*SafetyEvtCallback)(SafetyLevel, String, uint8_t);

/************************************************
 * Class
 *************************************************/

class EventMonitor
{
public:
    static EventMonitor &getInstance()
    {
        static EventMonitor instance;
        return instance;
    }

    void onSafetyEvent(SafetyEvtCallback callback);
    void onMessage(MessageCallback callback);
    void onError(ErrorCallback callback);
    void sendMessage(String msg);
    void sendError(uint8_t errorCode, String errorMsg);
    void reportSafetyEvent(SafetyLevel level, String message, uint8_t componentId = 0);

private:
    EventMonitor() : messageCallback(nullptr), errorCallback(nullptr) {}
    EventMonitor(const EventMonitor&) = delete;
    EventMonitor& operator=(const EventMonitor&) = delete;
    
    MessageCallback messageCallback;
    ErrorCallback errorCallback;
    SafetyEvtCallback safetyEvtCallback;

    void _onMessage(String msg);
    void _onError(uint8_t errorCode, String errorMsg);
    void _onSafetyEvent(SafetyLevel level, String msg, uint8_t componentId);
};

#endif // EVENT_MONITOR_H