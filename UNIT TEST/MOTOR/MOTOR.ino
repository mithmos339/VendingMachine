const int in11 = 7;
const int in12 = 8;
const int in21 = 2;
const int in22 = 4;

void setup()
{
    pinMode (in11,OUTPUT);
    pinMode (in12,OUTPUT);
    pinMode (in21,OUTPUT);
    pinMode (in22,OUTPUT);
    Serial.begin(9600);

}

void loop()
{
    digitalWrite (in11,LOW);
    digitalWrite (in12,HIGH);
    delay(5000);
    digitalWrite (in21,LOW);
    digitalWrite (in22,HIGH);
    delay(5000);
}