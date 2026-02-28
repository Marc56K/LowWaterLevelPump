#include "Relay.h"

void Relay::init()
{
    pinMode(RELAY_PIN, INPUT);
}

void Relay::update()
{
    unsigned long now_ms = millis();
    
    auto relay_state_sec = (now_ms - _last_switch_ms) / 1000;

    if (_relay_is_on)
    {
        if (relay_state_sec > MAX_PUMP_ON_IN_SEC)
        {
            trySwitchRelay(now_ms, false);
        }
        else if (relay_state_sec > MIN_PUMP_ON_IN_SEC)
        {
            trySwitchRelay(now_ms, _requested_on);
        }
    }
    else if (relay_state_sec > MIN_PUMP_OFF_IN_SEC)
    {
        trySwitchRelay(now_ms, _requested_on);
    }
}

void Relay::request(bool on)
{
    _requested_on = on;
    update();
}

bool Relay::isOn() const
{
    return _relay_is_on;
}

uint16_t Relay::getSwitchCount() const
{
    return _relay_switch_count;
}

void Relay::trySwitchRelay(unsigned long now_ms, bool on)
{
    if (_relay_is_on != on)
    {
        _last_switch_ms = now_ms;
        _relay_is_on = on;
        ++_relay_switch_count;

        if (on)
        {
            Serial.println("relay on");
            pinMode(RELAY_PIN, OUTPUT);
            digitalWrite(RELAY_PIN, RELAY_ACTIVE);
        }
        else
        {
            Serial.println("relay off");
            pinMode(RELAY_PIN, INPUT);
        }
    }
}