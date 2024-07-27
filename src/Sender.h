#pragma once
#include <Arduino.h>
#include <RH_ASK.h>

struct RcData
{
    int sensor_value = 0;
    bool relay_active = false;
};

class Sender
{
public:
    Sender();
    void init();
    void send(const RcData& data);

private:
    unsigned long _last_send = 0;
    RcData _last_data;
    RH_ASK _rc433_sender;
};