#pragma once
#include <Arduino.h>
#include "config.h"

class Relay
{
public:
    void init();
    void request(bool on);
    bool isOn() const;
    uint16_t getSwitchCount() const;
    void update();

private:
    void trySwitchRelay(unsigned long now_ms, bool on);

    bool _requested_on = false;
    bool _relay_is_on = false;
    uint16_t _relay_switch_count = 0;
    unsigned long _last_update_ms = 0;
    unsigned long _last_switch_ms = 0;
};