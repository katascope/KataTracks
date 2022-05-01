//Reading: https://docs.microsoft.com/en-us/dotnet/core/compatibility/interop/5.0/built-in-support-for-winrt-removed
using System;
using System.Text;
using System.Threading;

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
            DeviceManagerBLE.StartMonitoring(null);
        }

        public static void StopMonitoring()
        {
            keepListening = false;
        }
    }
}
