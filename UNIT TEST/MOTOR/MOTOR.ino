const int in0 = 7;
const int in1 = 8;
const int in2 = 2;
const int in3 = 4;

void setup()
{
    pinMode (in0,OUTPUT);
    pinMode (in1,OUTPUT);
    pinMode (in2,OUTPUT);
    pinMode (in3,OUTPUT);
    Serial.begin(9600);

}

void loop()
{
    digitalWrite (in0,LOW);
    digitalWrite (in1,HIGH);
    delay(5000);
    digitalWrite (in2,HIGH);
    digitalWrite (in3,LOW);
    delay(5000);
}