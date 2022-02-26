//Reading: https://docs.microsoft.com/en-us/dotnet/core/compatibility/interop/5.0/built-in-support-for-winrt-removed
using System;
using System.Text;
using System.Threading;
using System;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace KataTracks
{
    class DeviceWatcher
    { 
        static public Thread bleListenerThread = null;
        static public Thread btListenerThread = null;
        static public bool keepListening = true;
        static public string bleMonitorLog = "";
        static public string btMonitorLog = "";

        static private void ListenToConnected(object in_name)
        {
            while (keepListening)
            {
                btMonitorLog = "Inactive BT:\n";
                bleMonitorLog = "Inactive BLE:\n";
                Thread.Sleep(1);
            }
        }

        static private void MonitorBluetoothDevices(object in_name)
        {
            while (keepListening)
            {
                BluetoothClient client = new BluetoothClient();
                var pds = client.PairedDevices;
                string tempLog = "Monitoring BT\n";
                foreach (var pd in pds)
                {
                    if (pd.DeviceName.Contains("Lightsuit") || pd.DeviceName.Contains("LightSuit"))
                    {
                        DeviceManagerBT.EnsureConnection(pd.DeviceAddress, pd.DeviceName);
                        tempLog += "+" + pd.DeviceName + " " + pd.DeviceAddress + " " + (pd.Connected ? "online" : "offline") + "\n";
                    }
                    else tempLog += "-" + pd.DeviceName + " " + pd.DeviceAddress + "\n";
                }
                btMonitorLog = tempLog;

                Thread.Sleep(5000);
            }
        }

        static private void MonitorBLEDevices(object in_name)
        {
            while (keepListening)
            {
                /*bleMonitorLog = "MonitoringBLE ("+ DeviceManagerBLE.discoveredBLE.Count+")\n";
                foreach (KeyValuePair<string,string> kvp in DeviceManagerBLE.discoveredBLE)
                {
                    bleMonitorLog += " " + kvp.Key + " : " + kvp.Value + "\n";
                }
                foreach (KeyValuePair<string, string> kvp in DeviceManagerBLE.discoveredBLE)
                {
                    DeviceManagerBLE.poll();
                }*/
            }
        }


        private static bool _isMonitoring = false;
        public static bool IsMonitoring() { return _isMonitoring; }  
        public static void StartMonitoring()
        {
            _isMonitoring = true;
            bleListenerThread = new Thread(MonitorBLEDevices);
            bleListenerThread.Start("BLEDeviceWatcher");

            btListenerThread = new Thread(MonitorBluetoothDevices);
            btListenerThread.Start("BTDeviceWatcher");


            DeviceManagerBLE.StartMonitoring(null);
        }

        public static void StopMonitoring()
        {
            keepListening = false;
        }
    }
}
