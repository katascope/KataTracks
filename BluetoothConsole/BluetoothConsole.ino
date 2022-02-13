#include <SoftwareSerial.h>
SoftwareSerial BTSerial(5, 6); // RX | TX

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter Serial Commands");
  BTSerial.begin(38400); // HC-05 default speed in AT command more
}

void loop()
{ 
  if (BTSerial.available())
  {
    String data = BTSerial.readString();
    BTSerial.print(data); //Don't enable this if AT mode
    Serial.print(data);
  }
  
  if (Serial.available()) 
  {
    String data = Serial.readString();
    Serial.print(data);
    BTSerial.print(data);
  }
}
