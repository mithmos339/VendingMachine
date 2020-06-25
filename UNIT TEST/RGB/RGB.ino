int redpin = 3; //select the pin for the red LED
int bluepin = 6; // select the pin for the  blue LED
int greenpin = 5;// select the pin for the green LED

int val;

void setup() {
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  for(val = 255; val > 0; val--)
  {
    analogWrite(redpin, val);  //set PWM value for red
    analogWrite(bluepin, 255 - val); //set PWM value for blue
    analogWrite(greenpin, 128 - val); //set PWM value for green
    delay(1); 
  }
  for(val = 0; val < 255; val++)
  {
    analogWrite(redpin, val);
    analogWrite(bluepin, 255 - val);
    analogWrite(greenpin, 128 - val);
    delay(1); 
  }
}