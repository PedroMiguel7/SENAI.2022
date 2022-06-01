// C++ code
//
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  digitalWrite(12, HIGH);
  delay(800);
  digitalWrite(10, HIGH);
  delay(200); 
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  delay(800); 
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(800); 
  digitalWrite(12, HIGH);
  delay(200);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
}