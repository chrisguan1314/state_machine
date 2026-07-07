#pragma once

#include <stdint.h>

class EventOpen
{
private:
    bool flag_{false};
    uint8_t tytpe_{0};
};

class EventExit
{
private:
    bool flag_{false};
    uint8_t tytpe_{0};
};

class EventActive
{
private:
    bool flag_{false};
    uint8_t tytpe_{0};
};

class EventSuspend
{
private:
    bool flag_{false};
    uint8_t tytpe_{0};
};

class EventTerminate
{
private:
    bool flag_{false};
    uint8_t tytpe_{0};
};

class EventBase
{
    EventOpen open_event_;
    EventExit exit_event_;
    EventActive active_event_;
    EventSuspend suspend_event_;
    EventTerminate terminate_event_;
};