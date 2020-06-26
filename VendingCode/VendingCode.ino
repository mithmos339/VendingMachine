#include "SPI.h"
#include "MFRC522.h"
#include "TM1637.h"
#include <Keypad_I2C.h>
#include <Wire.h>
#include <Keypad.h>

#define I2CADDR 0x20
#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8

// Set 7-Secment Analog
const int CLK = 15;
const int DIO = 14;

// Set RGB
int redpin = 3; //select the pin for the red LED
int greenpin = 6; // select the pin for the  blue LED
int bluepin = 5;// select the pin for the green LED

//Set Motor Driver
const int in11 = 7;
const int in12 = 8;
const int in21 = 2;
const int in22 = 4;

//Set KEYPAD
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

int E = 10; // เหรียญ                 //เปลี่ยนค่าราคาสินค้าและค่าของเงินใน ARDUINO 
int F = 20; // ธนบัตร
int ProductA = 5; // ราคาสินค้า A
int ProductB = 10; // ราคาสินค้า B

int num1 = 0; // เงินรวม
int num2, num3; // จำนวนสินค้า , เงินค่าสินค้ารวม
int d; // วินาที * จำนวนสินค้า
char op; // A or B
bool presentValue = false;
bool final = false;
int cne = 0; //ค่าเหรียญ++
int cnf = 0; //ค่าธนบัตร++

Keypad_I2C kpd(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574); // KEYPAD
MFRC522 rfid(SS_PIN, RST_PIN); // RFID
MFRC522::MIFARE_Key key; // RFID
TM1637 sevenSegment(CLK, DIO); // 7-Secment

void setup() {
  Serial.begin(9600);
  sevenSegment.displayStr("  00");
  SPI.begin();
  rfid.PCD_Init();
  Wire.begin();
  kpd.begin(makeKeymap(keys));
  Serial.println("Start");
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode (in11,OUTPUT);
  pinMode (in12,OUTPUT);
  pinMode (in21,OUTPUT);
  pinMode (in22,OUTPUT);
}

void loop() {
  char key = kpd.getKey();
  
  if(key != NO_KEY && num1 >= 5)
  {
    analogWrite(bluepin, 0);
    analogWrite(redpin, 0);
    analogWrite(greenpin, 1);
  }
    if (key != NO_KEY && (key == 'A'|| key == 'B')) {
        if (presentValue != true && key == 'A')
        {
            op = key;
            sevenSegment.displayStr("   A");
            analogWrite(bluepin, 1);
            analogWrite(redpin, 0);
            analogWrite(greenpin, 0);
        }
        if (presentValue != true && key == 'B')
        {
            op = key;
            sevenSegment.displayStr("   B");
            analogWrite(bluepin, 0);
            analogWrite(redpin, 1);
            analogWrite(greenpin, 0);
        }
        final = true;
    }
    if (presentValue == false && key != NO_KEY && (key == '1'||key == '2'||key == '3'||key == '4'||key == '5'||key == '6'||key == '7'||key == '8'||key == '9')) {
        if(presentValue == false)
        {
            presentValue = true;
            num2 = key - 48;
            sevenSegment.displayNum(num2);
        }
    }
    else if (final == true && key != NO_KEY && key == 'C') {
        if (op == 'A')
        {
            num3 = num2 * ProductA;
            if (op == 'A' && num3 <= num1)
            {
                num1 = num1 - num3;
                sevenSegment.displayNum(num1);
                d = num2 * 500;
                digitalWrite (in11,LOW);
                digitalWrite (in12,HIGH);
                delay(d);
                digitalWrite (in11,0);
                digitalWrite (in12,0);
            }
            else 
            {
                digitalWrite (in11,0);
                digitalWrite (in12,0);
            }
        }
        else if (op == 'B')
        {
            num3 = num2 * ProductB;
            if (op == 'B' && num3 <= num1)
            {
                num1 = num1 - num3;
                sevenSegment.displayNum(num1);
                d = num2 * 500;
                digitalWrite (in21,LOW);
                digitalWrite (in22,HIGH);
                delay(d);
                digitalWrite (in21,0);
                digitalWrite (in22,0);
            }
            else 
            {
                digitalWrite (in21,0);
                digitalWrite (in22,0);
            }
        }
    }
    else if (key != NO_KEY && key == 'D')
    {
        sevenSegment.displayNum(num1);
        presentValue = false;
        final = false;
        num1;
        num2 = 0;
        num3 = 0;
        op = ' ';
    }
    if (num1 < 5) {
            analogWrite(bluepin, 0);
            analogWrite(redpin, 0);
            analogWrite(greenpin, 0);
    }
    if (num1 == 0){
        sevenSegment.displayStr("   0");
    } 
        
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) 
    return;
    
    // Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    // Serial.println(rfid.PICC_GetTypeName(piccType));
  
    // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    return;  
   }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  // ตัวแปร strID จะเก็บค่า UID ของแท็กไว้แล้ว
  
    if (strID == "09:98:1A:C3") {
        delay(250);
        cne++;
        Serial.println(cne);
        analogWrite(greenpin, 1);
        analogWrite(redpin, 0);
        analogWrite(bluepin, 0);
    }
    if (strID == "E4:67:EC:2A") {
        delay(250);
        cnf++;
        Serial.println(cnf);
        analogWrite(greenpin, 1);
        analogWrite(redpin, 0);
        analogWrite(bluepin, 0);
    }
    num1 = (E * cne) + (F * cnf);
    sevenSegment.displayNum(num1);
    return;
  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
   
}

