//https://docs.microsoft.com/en-us/windows/uwp/devices-sensors/gatt-client
using System;
using System.Collections.Generic;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using System.Threading.Tasks;

namespace ConsoleBLE
{
    public class BleSearch
    {
        public static void DoSearch()
        {
            Console.WriteLine("Searching for Advertised LightSuits");
            // Create Bluetooth Listener
            var watcher = new BluetoothLEAdvertisementWatcher();

            watcher.ScanningMode = BluetoothLEScanningMode.Active;

            // Only activate the watcher when we're recieving values >= -80
            watcher.SignalStrengthFilter.InRangeThresholdInDBm = -80;

            // Stop watching if the value drops below -90 (user walked away)
            watcher.SignalStrengthFilter.OutOfRangeThresholdInDBm = -90;

            // Register callback for when we see an advertisements
            watcher.Received += OnAdvertisementReceived;

            // Wait 5 seconds to make sure the device is really out of range
            watcher.SignalStrengthFilter.OutOfRangeTimeout = TimeSpan.FromMilliseconds(5000);
            watcher.SignalStrengthFilter.SamplingInterval = TimeSpan.FromMilliseconds(2000);

            // Starting watching for advertisements
            watcher.Start();
        }
        
        static bool inProcess = false;
        static Dictionary<ulong, bool> searched = new Dictionary<ulong, bool>();
        private static void OnAdvertisementReceived(BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs)
        {

            //if (eventArgs.Advertisement.LocalName.Contains("LightSuitA") || eventArgs.Advertisement.LocalName.Contains("LightsuitA"))
            {
                if (!searched.ContainsKey(eventArgs.BluetoothAddress))
                {
                    Console.WriteLine(String.Format("Found:" + eventArgs.Advertisement.LocalName + " / " + eventArgs.Advertisement.ServiceUuids.ToString()));
                    if (!inProcess)
                    {
                        inProcess = true;
                        // Tell the user we see an advertisement and print some properties
                        Console.WriteLine(String.Format("Advertisement:"));
                        Console.WriteLine(String.Format("  BT_ADDR: {0}", eventArgs.BluetoothAddress));
                        Console.WriteLine(String.Format("  FR_NAME: {0}", eventArgs.Advertisement.LocalName) + "\n");

                        searched[eventArgs.BluetoothAddress] = true;
                        //ConnectDevice(eventArgs.BluetoothAddress);
                        inProcess = false;
                        //Console.WriteLine(log);
                    }
                }
                else Console.WriteLine("Already searched " + eventArgs.BluetoothAddress);
            }
            //else Console.WriteLine(String.Format("Skipping:" + eventArgs.Advertisement.LocalName + " / " + eventArgs.Advertisement.ServiceUuids.ToString()));
        }

    }
}
