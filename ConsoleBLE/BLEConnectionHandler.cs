//https://docs.microsoft.com/en-us/windows/uwp/devices-sensors/gatt-client
using System;
using Windows.System;
using System.Collections.Generic;
using Windows.Devices.Enumeration;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Storage.Streams;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleBLE
{
    class BLEConnectionHandler
    {

        static void Main(string[] args)
        {
            // Start the program
            var connectionHandler = new BLEConnectionHandler();

            // Close on key press
            //Console.ReadLine();
            while (!Console.KeyAvailable)
            {
                foreach (KeyValuePair<string, BLEDevice> device in DeviceManagerBLE.devices)
                {
                    Console.WriteLine("Scanning {0} : {1}", device.Value.device.Name, device.Value.device.ConnectionStatus);
                }
            }
        }
        public BLEConnectionHandler()
        {
            DeviceManagerBLE.DoSearch();

            //DoDirectConnections();
        }

    }
}
