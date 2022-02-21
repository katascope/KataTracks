//Used for doing AT commands to bluetooth via serial. Do not use for general terminal usage.
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(5, 6); // RX | TX

/*
  HC-05 AT Commands
  Function                | Command                  | Response         | Parameter
  Test                    | AT                       | OK               | None
  Name                    | AT+NAME?                 | +NAME:HC-05, OK  | HC-05 (Default)
  Password                | AT+PSWD?                 | +PSWD:1234, OK   | 1234 (Default)
  Change Name             | AT+NAME = <name>         | OK               | None
  Change Password         | AT+PSWD=<pswd>           | OK               | None
  UART                    | AT+UART?                 | +UART:38400,0,0  | 38400 (Default
  Connection mode         | AT+CMODE?                | +CMOD:<cmod>     | 0 (Default)<br>
  Connection mode set     | AT+CMODE=<cmode>         | Ok               | (0 (Connect to a specified 
  address)) >> (1 (Connect to any available address))
  Find Address            | AT+ADDR?                 | +ADDR:<addr>, OK | None
  Connect to Address      | AT+BIND=<addr>           | OK               | Replace the : with ,
  Reset Device            | AT+RESET                 | OK               | None
  Restore Factory Default | AT+ORGL                  | OK               | None
  */
void setup()
{
pinMode(9, OUTPUT); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
digitalWrite(9, HIGH);
  
Serial.begin(9600);
Serial.println("Enter AT commands:");
//seems to be 38400?
//getting E⸮=I⸮J⸮⸮ - this happens if you print btserial back to btserial causing looping
BTSerial.begin(38400); // HC-05 default speed in AT command more

}

void loop()
{ 
  if (BTSerial.available())
  {// read from HC-05 and send to Arduino Serial Monitor
    String data = BTSerial.readString();
    //BTSerial.print(data); //Don't enable this if AT mode
    Serial.print(data);
    //Serial.print("/");
    //Serial.print(String((int)data));
  }
  
  if (Serial.available()) 
  {
    String data = Serial.readString();
    Serial.print(data);
    BTSerial.print(data);
  }
}
