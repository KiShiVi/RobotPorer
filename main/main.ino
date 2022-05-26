#include "brain.hpp"

Brain * brain;

void setup() {
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  //digitalWrite(6, LOW);
  
  Serial.begin(9600);
  brain = new Brain();
}

void loop() {
  brain->tick();
}

extern int __bss_end;
extern void *__brkval;

int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
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
