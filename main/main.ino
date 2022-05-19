#include "brain.hpp"

Brain * brain;

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(5, INPUT);
  Serial.begin(9600);
  brain = new Brain();
}

void loop() {
    brain->tick();
}

//#include "slot.hpp"
//#include "servocrane.hpp"
//
//ServoCrane * servo;
//Pump * pump;
//LedStrip * ledStrip;
//Slot * slot;
//Slot * slot2;
//
//void setup()
//{
//  servo = new ServoCrane( 5 );
//  pinMode(3, INPUT_PULLUP);
//  pinMode(8, INPUT_PULLUP);
//  Serial.begin(9600);
//  pinMode(5, INPUT);
//  pump = new Pump(2);
//  ledStrip = new LedStrip();
//  slot = new Slot( ledStrip, pump, servo, 3, 0, 120 );
//  slot2 = new Slot( ledStrip, pump, servo, 8, 1, 60 );
//}
//
//void loop()
//{
//  pump->pumpCheck();
//  slot->slotFirstCheck();
//  slot2->slotFirstCheck();
//  slot->slotSecondCheck();
//  slot2->slotSecondCheck();
//  slot->slotThirdCheck();
//  slot2->slotThirdCheck();
//  delay(100);
//}
