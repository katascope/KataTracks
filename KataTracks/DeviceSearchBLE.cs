//Reading: https://docs.microsoft.com/en-us/dotnet/core/compatibility/interop/5.0/built-in-support-for-winrt-removed
using System;
using System.Text;
using System.Threading;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Collections.Concurrent;
using InTheHand.Bluetooth;

namespace KataTracks
{
    public class DeviceSearchBLE
    {
        private static BluetoothLEScanFilter scanFilter = new BluetoothLEScanFilter();
        private static RequestDeviceOptions rdo = new RequestDeviceOptions();
        private static Dictionary<string, string> discoveredBLE = new Dictionary<string, string>();
        private static IReadOnlyCollection<BluetoothDevice> discoveredDevices = null;
        public static async Task<Dictionary<string, string>> DiscoverDevicesAsync()
        {
            scanFilter = new BluetoothLEScanFilter();
            rdo = new RequestDeviceOptions();
            discoveredBLE = new Dictionary<string, string>();
            scanFilter.NamePrefix = "Light";
            rdo.Filters.Add(scanFilter);
            discoveredDevices = await Bluetooth.ScanForDevicesAsync();            

            foreach (BluetoothDevice bd in discoveredDevices)
            {
                if (bd.Name.Contains("LightSuit") || bd.Name.Contains("Lightsuit"))
                {
                    if (!discoveredBLE.ContainsKey(bd.Id))
                    {
                        discoveredBLE[bd.Id] = bd.Name;
                    }
                }
            }
            return discoveredBLE;
        }
    }
}