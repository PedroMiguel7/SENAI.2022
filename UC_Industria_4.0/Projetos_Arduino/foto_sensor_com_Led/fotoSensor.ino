// C++ code
//
int pinoLed = 12;
int pinoLed2 = 10;
int pinoLed3 = 8;

int pinoSensorLuz = A0;
int valorLuz = 0;
void setup()
{
  pinMode(pinoSensorLuz, INPUT);
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoLed2, OUTPUT);
  pinMode(pinoLed3, OUTPUT);
}
void loop()
{
  valorLuz = analogRead(pinoSensorLuz);
  if(valorLuz<250)
  {
    digitalWrite(pinoLed3, HIGH);
  }
  else
  {
    digitalWrite(pinoLed3, LOW);
  }
  if(valorLuz<450)
  {
    digitalWrite(pinoLed2, HIGH);
  }
  else
  {
    digitalWrite(pinoLed2, LOW);
  }
  if(valorLuz<650)
  {
    digitalWrite(pinoLed, HIGH);
  }
  else
  {
    digitalWrite(pinoLed, LOW);
  }
}