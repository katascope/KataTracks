# KataTracks
What it should be: Wireless light-suits precisely synchronized to events in the music.
Lightsuit.. Songtracksuit?

Mark 1 : 
 System: Arduino Nano
 Case: 3d-printed for Nano
 Power: XT30 connection (can adapt to XT60)
 Output: BTF-Lighting Connector
Mark 2 : Wireless
 Wireless: HC-05 Bluetooth
Mark 3
 System: Arduino Nano OR Pro Micro
 Case: 3d-printed for Nano
 Power: XT30 connection (can adapt to XT60)
 Output: BTF-Lighting Connector
 Wireless: HC-05 Bluetooth
Additions:
 Accelerometer
 128x32 OLED display



   Design Criteria:
    Audioreactive : The device must represent the dance music.
    Lead-Follow : The follow device can synchronize with the lead device.
    Simple : The device must be extremely easy to use once setup.
    Reliable : The software must work correctly during the dance.
     Care with overloading bluetooth buffer
     Startup 3 seconds for led safety
    Minimal : The device must strenously optimize RAM usage.
     PROGMEM for Track - Can expand without using RAM
     See: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
    Configurable : The code must be highly configurable by #DEFINE.
    Recoverable : The device should be able to recover from mistimings.
    Cheap : The device must be low cost and easy to produce.
    Portable : The device must be human wearable and untethered.
    Stable : The device must withstand repeated heavy use dancing.
    Subtle : Indirect lighting for led's, hazed frosted fogged.
    Compatible : The device must maximize use of standards.
     Arduino Nano : Standard microcontroller kit
     WS2811 : Addressable LED wire : Standard 3-wire connectors
     BTF-Lighting Connectors : Addressable 3-wire LED wire connectors
     Also used for power connector into arduino.
     XT-60 Battery connector with D-Sun BEC Voltage convert (3-cell 12v down to 5v)
      or 18650 Battery Shield case using 5-V output
     Thingiverse Case & plans
     ffmpeg for Spectrum Analysis
     HC-05 Bluetooth https://www.evelta.com/blog/instructions-to-set-bluetooth-module-hc05-password-using-arduino/
      AT+NAME?
      AT+NAME="LedLight"
      AT+PSWD="3838"
     Master+Slave BT bindings: https://www.instructables.com/Arduino-Bluetooth-Master-and-Slave-Using-Any-HC-05/
   Tradeoffs:
     Audio track setup does not have to be easy or quick.
     Different arduinos can be used.
     Different forms of power/battery can be used.
     Arduino Micro Pro can be used if possible instead of Arduino Nano
   Aesthetic Criteria:
     Tasteful : Use complex colors, avoid 'rgb rainbow land'
     Smooth : Fading color transitions over palette rotations
     Fade-To interpolated timing so endings match startings
   To create a spectrum analysis for use in creating the events:
     Use ffmpeg with a size of (song length * 10). ex 205 seconds * 10 = 2050x512 as below.
      ex. ffmpeg -i "game.m4a" -lavfi showspectrumpic=s=2050x512:color=4:scale=lin:stop=8000 gameLd.png
   Ideas:
    https://learn.sparkfun.com/tutorials/prototype-wearable-led-dance-harness/all
    https://learn.sparkfun.com/tutorials/motion-controlled-wearable-led-dance-harness
    https://learn.sparkfun.com/tutorials/hackers-in-residence---sound-and-motion-reactivity-for-wearables
   Radio: dw
    NRF24L01 https://www.instructables.com/Arduino-and-NRF24L01/
    RTF433 https://www.instructables.com/RF-315433-MHz-Transmitter-receiver-Module-and-Ardu/
   JY-MCU Bluetooth module communication example for Arduino.
    Connect RX_PIN to TX pin of the module,
    Connect TX_PIN to RX pin of the module.
   Set Bluetooth HC-05

   16k - For a bluetooth-enabled 300-addressableled-driving music-synchronized system

   //Accelerometer: https://electropeak.com/learn/interfacing-mma7361-accelerometer-module-with-arduino/
