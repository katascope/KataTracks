#include <Arduino.h>

void PrintLoglno(String str)
{
  Serial.print(F("Lognolen="));
  Serial.print(str.length());
  Serial.println(str);
}
void setup() {
  Serial.begin(9600); //serial communication at 9600 bauds
  Serial.println(F("Serial Ok"));
  delay( 3000 ); // power-up safety delay
  Serial.println(F("3-second delay done."));
  String s = "Log test";
  PrintLoglno(s);
  
}

void loop()
{
  
}
