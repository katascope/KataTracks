using System;
using System.Threading;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace HandBLE
{
    class Program
    {
        static void DoSearch()
        {
            Console.WriteLine("Searching for BLE (30sec)\n");
            var t = Task.Run(() => DeviceSearchBLE.DiscoverDevicesAsync());
            Dictionary<string, string> devicesBLE = t.Result;
            foreach (KeyValuePair<string, string> kvp in devicesBLE)
                Console.WriteLine("Found: " + kvp.Key + " : " + kvp.Value);
            Console.WriteLine("Search complete");

            while (!Console.KeyAvailable) { }
        }

        static void Main(string[] args)
        {
            DoSearch();return;

            List<string> connectionList = new List<string>() { 
                "FA642247BCCD",
                //"FDB857FE7C3D",
                "CA8E42F29042"
            };

            DeviceManagerBLE.StartMonitoring(connectionList);

            while (!Console.KeyAvailable)
            {
                foreach (KeyValuePair<string, BleDevice> kvp in DeviceManagerBLE.bleDevices)
                    Console.Write(kvp.Key + " : " + kvp.Value.serviceCache.Count + " ");
                if (DeviceManagerBLE.bleDevices.Count > 0) Console.WriteLine();
                Thread.Sleep(1000);
            }

            DeviceManagerBLE.SendMessage("0\r\n");
            DeviceManagerBLE.DisconnectAll();
        }
    }
}
