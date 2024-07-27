#pragma once
#include <Arduino.h>
#include "config.h"

class Relay
{
public:
    void init();
    void active(bool on);
    bool isActive();
    void update();

private:
    void switchRelay(unsigned long now, bool on);

    bool _requested_on = false;
    bool _relay_is_on = false;
    unsigned long _last_update_ms = 0;
    unsigned long _last_switch_ms = 0;
    unsigned long _on_duration_ms = 0;
    unsigned long _cooldown_duration_ms = 0;
};