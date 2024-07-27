#include "Relay.h"

void handleTimeOverflow(unsigned long now, unsigned long &t)
{
    if (now < t)
        t = 0;
}

void Relay::init()
{
    pinMode(RELAY_PIN, INPUT);
}

void Relay::update()
{
    unsigned long now_ms = millis();
    handleTimeOverflow(now_ms, _last_update_ms);
    handleTimeOverflow(now_ms, _last_switch_ms);

    unsigned long delta_t = now_ms - _last_update_ms;
    _last_update_ms = now_ms;

    if (_relay_is_on)
    {
        _on_duration_ms += delta_t;
    }

    if (_cooldown_duration_ms > 0)
    {
        _cooldown_duration_ms -= min(_cooldown_duration_ms, delta_t);
    }

    if (_cooldown_duration_ms == 0)
    {
        switchRelay(now_ms, _requested_on);
    }

    if (_relay_is_on && (_on_duration_ms / 1000) > MAX_PUMP_DURATION_IN_SEC)
    {
        Serial.println("relay cooldown");
        switchRelay(now_ms, false);
        _cooldown_duration_ms = 1000ul * PUMP_COOL_DOWN_IN_SEC;
    }
}

void Relay::active(bool on)
{
    _requested_on = on;
    update();
}

bool Relay::isActive()
{
    return _requested_on;
}

void Relay::switchRelay(unsigned long now, bool on)
{
    if (on != _relay_is_on)
    {
        _last_switch_ms = now;
        _relay_is_on = on;
        if (on)
        {
            Serial.println("relay on");
            _on_duration_ms = 0;
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