#include "Sender.h"
#include "config.h"

Sender::Sender():
    _rc433_sender(2000, /*RX*/ -1, /*TX*/ RC433_DATA_PIN, RC433_POWER_PIN)
{

}

void Sender::init()
{
    if (!_rc433_sender.init())
        Serial.println("init RC433 failed!");
}

void Sender::send(const RcData& data)
{
    unsigned long now = millis();
    bool data_changed = _last_data.relay_active != data.relay_active;
    unsigned long interval = data_changed ? RC433_MIN_SEND_INTERVAL_IN_SEC : RC433_MAX_SEND_INTERVAL_IN_SEC;
 
    if (_last_send > now || (now - _last_send) > interval * 1000)
    {
        String msg('{');
        msg += String("\"id\":\"P") + String(RC433_DEVICE_ID) + String("\",");
        msg += String("\"t\":") + String(millis() / 1000) + ',';
        msg += String("\"s\":") + String(data.sensor_value) + ',';
        msg += String("\"r\":") + String(data.relay_active) + '}';
        if (!_rc433_sender.send((uint8_t *)msg.c_str(), msg.length()) || !_rc433_sender.waitPacketSent())
        {
            Serial.println("sending data failed");
            return;
        }
        _last_send = millis();
        _last_data = data;
    }
}