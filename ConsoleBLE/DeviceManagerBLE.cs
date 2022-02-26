//https://docs.microsoft.com/en-us/windows/uwp/devices-sensors/gatt-client
using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using System.Threading.Tasks;

namespace ConsoleBLE
{
    public class BLEDevice : IDisposable
    {
        public BluetoothLEDevice device;
        public GattDeviceServicesResult servicesResult;
        public Dictionary<string, Dictionary<string, GattCharacteristic>> api = new Dictionary<string, Dictionary<string, GattCharacteristic>>();

        public GattCharacteristic GetCharacteristic(string serviceUuid, string characteristiUuid)
        {
            if (api.ContainsKey(serviceUuid) && api[serviceUuid].ContainsKey(characteristiUuid))
                return api[serviceUuid][characteristiUuid];
            else return null;
        }
        public void Dispose()
        {
            device.Dispose();
        }
    }
    public class DeviceManagerBLE
    {
        public static string log = "";
        public static ConcurrentDictionary<ulong, BLEDevice> devices = new ConcurrentDictionary<ulong, BLEDevice>();

        public static async Task ConnectDevice(ulong bluetoothDeviceId)
        {
            if (!devices.ContainsKey(bluetoothDeviceId))
            {
                devices[bluetoothDeviceId] = new BLEDevice();
            }
        }

        public static async Task ConnectDeviceLiteral(ulong bluetoothDeviceId)
        {
            using (BLEDevice bled = new BLEDevice())
            {

                // Note: BluetoothLEDevice.FromIdAsync must be called from a UI thread because it may prompt for consent.
                //BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);
                Console.WriteLine("Connecting " + bluetoothDeviceId);

                bled.device = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);
                Console.WriteLine("<<" + bled.device.ConnectionStatus);
                Console.WriteLine("Bluetooth Name:" + bled.device.Name);
                Console.WriteLine("Bluetooth DeviceId:" + bled.device.DeviceId);

                bled.servicesResult = await bled.device.GetGattServicesForUuidAsync(new Guid("02FE4875-5056-48B5-AD15-36E30665D9B4"));
                //bled.servicesResult = await bled.device.GetGattServicesAsync();
                if (bled.servicesResult.Status == GattCommunicationStatus.Success)
                {
                    foreach (GattDeviceService service in bled.servicesResult.Services)
                        Console.WriteLine(" Service:" + service.Uuid);

                    Console.WriteLine("Service fetch start");
                    var services = bled.servicesResult.Services;
                    Console.WriteLine("Service fetch done");

                    if (services.Count == 0)
                        Console.WriteLine("No services found.");

                    foreach (GattDeviceService service in services)
                    {
                        Console.WriteLine(" Service:" + service.Uuid);
                        GattCharacteristicsResult cresult = await service.GetCharacteristicsAsync();
                        bled.api[service.Uuid.ToString()] = new Dictionary<string, GattCharacteristic>();
                        if (cresult.Status == GattCommunicationStatus.Success)
                        {
                            var characteristics = cresult.Characteristics;
                            foreach (GattCharacteristic characteristic in characteristics)
                            {
                                bled.api[service.Uuid.ToString()][characteristic.Uuid.ToString()] = characteristic;
                                Console.WriteLine("  Characteristic:" + characteristic.Uuid);
                                GattCharacteristicProperties properties = characteristic.CharacteristicProperties;
                                if (properties.HasFlag(GattCharacteristicProperties.Write))
                                {
                                    Console.WriteLine("   Write");
                                }
                                if (properties.HasFlag(GattCharacteristicProperties.Read))
                                {
                                    Console.WriteLine("   Read: ");
                                }
                                if (properties.HasFlag(GattCharacteristicProperties.Notify))
                                {
                                    Console.WriteLine("   Notify");
                                }
                            }
                        }

                    }
                }
                else if (bled.servicesResult.Status == GattCommunicationStatus.Unreachable)
                {
                    Console.WriteLine("Remote device unreachable");
                }
                else Console.WriteLine("Failed");

                Console.WriteLine("GATT query complete.");
            }            
        }

        static void DisconnectDevices()
        {
            foreach (KeyValuePair<ulong, BLEDevice> device in devices)
            {
                Console.WriteLine("Disconnecting device: " + device.Key);
                devices[device.Key].device.Dispose();
            }
        }

    }
}
