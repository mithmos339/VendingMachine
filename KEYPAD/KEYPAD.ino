#include <Keypad.h>
#include <Keypad_I2C.h>
#include <Wire.h>

#define I2CADDR 0*20

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};

Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574 );

void setup() {
  Wire.begin();
  kpd.begin( makeLeymap(Keys) );
  Serial.begin(9600);
  Serial.println("Start");
}
void loop() {
  char key = kpd.getKey();
  if (key) {
    Serial.println(key);
  }
}