#include "TM1637.h"

const int CLK = 15;
const int DIO = 14;

TM1637 sevenSegment(CLK, DIO);

void setup() {
  sevenSegment.init();
  sevenSegment.set(7); // BRIGHT 0-7;

  sevenSegment.displayNum(10);
  delay(2000);

  sevenSegment.displayNum(1234);
  delay(2000);

  sevenSegment.displayStr("0FF");
  delay(2000);
}

int number = 0;

void loop() {
  sevenSegment.displayNum(number++);
  delay(100);
}