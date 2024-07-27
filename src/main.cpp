#include <Arduino.h>
#include "Sender.h"
#include "Sensor.h"
#include "Relay.h"

#include "config.h"

Sender sender;
Sensor sensor;
Relay relay;

void randomSetupSleep()
{
  pinMode(A1, INPUT);
  randomSeed(analogRead(A1));
  delay(random(1000));
}

void updateLed()
{
  static unsigned long last_led_change = 0;
  static int last_led_state = LOW;
  unsigned long now = millis();
  if (now < last_led_change || (now - last_led_change) >= 1000)
  {
    last_led_change = now;
    pinMode(LED_PIN, OUTPUT);
    last_led_state = last_led_state == LOW ? HIGH : LOW;
    digitalWrite(LED_PIN, last_led_state);
  }
}

void setup() 
{
  Serial.begin(115200);

  sender.init();
  sensor.init();
  relay.init();

  randomSetupSleep();

  Serial.println("ready");
}

void loop() 
{
  updateLed();
  sensor.update();
  relay.update();

  int sensor_value = sensor.getValue();
  Serial.println(sensor_value);

  if (sensor_value < PUMP_START_SENSOR_VALUE)
    relay.active(true);

  if (sensor_value > PUMP_STOP_SENSOR_VALUE)
    relay.active(false);

  RcData data;
  data.sensor_value = sensor_value;
  data.relay_active = relay.isActive();
  sender.send(data);

  delay(100);
}
