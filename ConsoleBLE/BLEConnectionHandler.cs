//https://docs.microsoft.com/en-us/windows/uwp/devices-sensors/gatt-client
using System;

namespace ConsoleBLE
{
    class BLEConnectionHandler
    {

        static void Main(string[] args)
        {
            //DeviceManagerBLE.di
            UInt64 lightsuitA = 222712357359682;
            UInt64 lightsuitB = 275307978800333;
            
            //Dev
            //DeviceManagerBLE.ConnectDevice(lightsuitA);
            //DeviceManagerBLE.ConnectDevice(lightsuitB);

            Console.WriteLine("Search activated");
            while (!Console.KeyAvailable)
            {
            }
        }
    }
}
