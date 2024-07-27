#pragma once
#include <Arduino.h>
#include "config.h"

class Sensor
{
public:
    void init();
    void update();
    int getValue();

private:
    int _valid_samples = 0;
    int _next_sample = 0;
    int _samples[MAX_SENSOR_SAMPLES];
};