#include "pump.hpp"

Pump * pump;

void setup()
{
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(5, INPUT);
  pump = new Pump(5);
}

void loop()
{
  pump->pumpCheck();
  if(!digitalRead(3))
    pump->pumpStart();
}
