#include "brain.hpp"

Brain * brain;

void setup() {
  // Делаем подтяжку на концевики, т.к. они запаяны без подтягивающих резисторов
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
  
  Serial.begin(9600);
  brain = new Brain();  //!< Инициализация мозгов
}

void loop() {
  brain->tick();
}
