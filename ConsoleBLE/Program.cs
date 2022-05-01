//https://docs.microsoft.com/en-us/windows/uwp/devices-sensors/gatt-client
using System;
using System.Collections.Generic;

namespace KataTracks
{
    class Program
    {

        static void Main(string[] args)
        {
            Console.WriteLine("Searching for nearby BLE devices...");
            var foundDevices = DeviceSearchBLE.DiscoverDevicesAsync().Result;
            Console.WriteLine("Nearby BLE device search complete.");
            
            string bleScanned = "";
            if (foundDevices != null)
            {
                bleScanned = "Found: " + foundDevices.Count + "\n";
                foreach (KeyValuePair<string, string> kvp in foundDevices)
                {
                    bleScanned += kvp.Value + " : " + kvp.Key + "\n";
                }
                Console.WriteLine(" * " + bleScanned);
            }
            
            Console.WriteLine("Done.");
        }
    }
}
