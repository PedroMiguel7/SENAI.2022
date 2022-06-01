#include <LiquidCrystal.h>
#include <locale.h>
// C++ code
//
int contador = 1;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  
  int contador = 1;
  while (contador <= 16)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Senai -_- ");
    delay(1000);
    contador++;
  }
  
}