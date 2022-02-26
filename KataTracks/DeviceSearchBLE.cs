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
        public static async Task<Dictionary<string, string>> DiscoverDevicesAsync()
        {
            BluetoothLEScanFilter scanFilter = new BluetoothLEScanFilter();
            scanFilter.NamePrefix = "Light";
            RequestDeviceOptions rdo = new RequestDeviceOptions();
            rdo.Filters.Add(scanFilter);
            var discoveredDevices = await Bluetooth.ScanForDevicesAsync();
            Dictionary<string, string> discoveredBLE = new Dictionary<string, string>();

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