//some code https://forum.arduino.cc/t/at-commands-set-hci/691083/4
//https://www.arduino.cc/en/Reference/ArduinoBLE
#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
static const char *deviceName = "LightSuitA";

static const char* greeting = "Hello World!";
BLEService greetingService("180C");  // User defined service
BLEStringCharacteristic greetingCharacteristic(
    "2A56",  // standard 16-bit characteristic UUID
    BLERead, 13); // remote clients will only be able to read this

void IMU_Setup()
{
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void IMU_Poll()
{
  float x, y, z;

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
        IMU.readAcceleration(x, y, z);
        Serial.print("Acc=");
        Serial.print(x);
        Serial.print('\t');
        Serial.print(y);
        Serial.print('\t');
        Serial.print(z);
        
        IMU.readGyroscope(x, y, z);
        Serial.print(" Gyr=");
        Serial.print(x);
        Serial.print('\t');
        Serial.print(y);
        Serial.print('\t');
        Serial.println(z);
  }  
}

void BLE_Setup()
{
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1);
  }

  BLE.setLocalName(deviceName);  // Set name for connection
  BLE.setDeviceName(deviceName);  // Set name for connection
  //BLE.setPassword("3838");
  BLE.setAdvertisedService(greetingService); // Advertise service
  greetingService.addCharacteristic(greetingCharacteristic); // Add characteristic to service
  BLE.addService(greetingService); // Add service
  greetingCharacteristic.setValue(greeting); // Set greeting string

  BLE.advertise();  // Start advertising
  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
}

void BLE_Poll()
{
  BLEDevice central = BLE.central();  // Wait for a BLE central to connect

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central MAC: ");
    // print the central's BT address:
    Serial.println(central.address());

    while (central.connected()){} // keep looping while connected
    
    // when the central disconnects, turn off the LED:
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());
  }
}

void setup() {
  Serial.begin(9600);    // initialize serial communication
  while (!Serial);
  IMU_Setup();
  BLE_Setup();  
  Serial.println("Ready.");
}

void loop() {
  IMU_Poll();
  BLE_Poll();
}
