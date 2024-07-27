#include "Sensor.h"
#include <ArduinoSort.h>

void Sensor::init()
{
    pinMode(SENSOR_PIN, INPUT);
    pinMode(SENSOR_VCC_PIN, INPUT);
}

void Sensor::update()
{
    pinMode(SENSOR_VCC_PIN, OUTPUT);
    digitalWrite(SENSOR_VCC_PIN, LOW);
    pinMode(SENSOR_PIN, INPUT_PULLUP);
    int value = analogRead(SENSOR_PIN);
    pinMode(SENSOR_PIN, INPUT);
    pinMode(SENSOR_VCC_PIN, INPUT);

    _samples[_next_sample] = value;
    _next_sample = (_next_sample + 1) % MAX_SENSOR_SAMPLES;

    _valid_samples = min(_valid_samples + 1, MAX_SENSOR_SAMPLES);
}

int Sensor::getValue()
{
    if (_valid_samples > 0)
    {
        _valid_samples = min(_valid_samples, MAX_SENSOR_SAMPLES);
        sortArray(_samples, _valid_samples);
        return _samples[(_valid_samples - 1) / 2];
    }
    return 0;
}