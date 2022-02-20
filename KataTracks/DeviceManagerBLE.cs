//Reading: https://docs.microsoft.com/en-us/dotnet/core/compatibility/interop/5.0/built-in-support-for-winrt-removed
using System;
using System.Text;
using System.Threading;
using System.Collections.Generic;
using System.Threading.Tasks;
using InTheHand.Bluetooth;

namespace KataTracks
{

    public class BleCacheCharacteristic
    {
        public BluetoothUuid uuid;
        public bool read;
        public bool write;
        public bool notify;
        public GattCharacteristic gattCharacteristic;
    }

    public class BleCacheService
    {
        public BluetoothUuid uuid;
        public GattService gattService;
        public Dictionary<BluetoothUuid, BleCacheCharacteristic> characteristics = new Dictionary<BluetoothUuid, BleCacheCharacteristic>();
    }

    public class BleDevice
    {
        public string id;
        public string name;
        public BluetoothDevice bluetoothDevice;
        public Dictionary<BluetoothUuid, BleCacheService> serviceCache = new Dictionary<BluetoothUuid, BleCacheService>();
        public string log = "";
    }

    public class DeviceManagerBLE
    {
        public static Dictionary<string, BleDevice> bleDevices = new Dictionary<string, BleDevice>();
        static BluetoothUuid mainServiceUuid = BluetoothUuid.FromGuid(new Guid("02FE4875-5056-48B5-AD15-36E30665D9B4"));
        static BluetoothUuid mainCommandUuid = BluetoothUuid.FromGuid(new Guid("220154BF-1DCE-4F03-85F0-7BA905D2D6B0"));
        static BluetoothUuid mainAuthenticateUuid = BluetoothUuid.FromGuid(new Guid("4C75BB42-5365-458D-A3EA-2B91339646B7"));
        static BluetoothUuid mainTimecodeUuid = BluetoothUuid.FromGuid(new Guid("10365297-362D-44FB-8807-A6AA13B1BD83"));
        static BluetoothUuid mainPlayUuid     = BluetoothUuid.FromGuid(new Guid("3B140EF5-0A72-4891-AD38-83B5A2595622"));
        static BluetoothUuid mainStatusUuid = BluetoothUuid.FromGuid(new Guid("D01C9106-91BD-4998-9554-85264D33ACB2"));
        static BluetoothUuid mainCounterUuid = BluetoothUuid.FromGuid(new Guid("612DD356-9632-48CF-A279-935D3D4EF242"));
        static BluetoothUuid mainCounterResetUuid = BluetoothUuid.FromGuid(new Guid("EA7CE01E-808B-4EF3-8735-2A05F1C48DFF"));

        public static int Count()
        {
            return bleDevices.Count;
        }

        public static BleDevice Get(string name)
        {
            if (bleDevices.ContainsKey(name))
                return bleDevices[name];
            else return null;
        }

        public static void DisconnectAll()
        {
            foreach (KeyValuePair<string,BleDevice> kvp in bleDevices)
            {
                BleDevice bd = kvp.Value;
                bd.bluetoothDevice.Gatt.Disconnect();
            }
        }

        public static async Task<bool> TryToGet(string id)
        {
            BluetoothDevice bd = await BluetoothDevice.FromIdAsync(id);
            if (bd != null)
                QueryGATT(bd);
            return false;
        }

        public static async void poll()
        {
            foreach (KeyValuePair<string, BleDevice> kvp in bleDevices)
            { 
                BleDevice bd = kvp.Value;
                if (bd.bluetoothDevice.Gatt != null)
                {
                    try
                    {
                        if (bd.serviceCache.Count > 0)
                        {
                            GattCharacteristic gattCharacteristicStatus = bd.serviceCache[mainServiceUuid].characteristics[mainStatusUuid].gattCharacteristic;
                            byte[] valuesStatus = await gattCharacteristicStatus.ReadValueAsync();
                            bd.log = String.Format("{0}-{1}-{2}", valuesStatus[3], valuesStatus[2], valuesStatus[1]);

                            GattCharacteristic gattCharacteristicTimecode = bd.serviceCache[mainServiceUuid].characteristics[mainTimecodeUuid].gattCharacteristic;
                            byte[] valuesTimecode = await gattCharacteristicTimecode.ReadValueAsync();
                            ulong timecode = BitConverter.ToUInt32(valuesTimecode, 0);
                            bd.log += String.Format("{0}", timecode);

                        }
                        else
                        {
                            QueryGATT(bd.bluetoothDevice);
                            bd.log = " waiting";
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Error unexpected! Ex[" + ex.Message + "]");
                    }
                }
            }
        }

        public static async void Play(ulong tc)
        {
            foreach (KeyValuePair<string, BleDevice> kvp in bleDevices)
            {
                BleDevice bd = kvp.Value;
                if (bd.bluetoothDevice.Gatt != null)
                {
                    try
                    {
                        if (bd.serviceCache.Count > 0)
                        {
                            GattCharacteristic gattCharacteristicCommand = bd.serviceCache[mainServiceUuid].characteristics[mainPlayUuid].gattCharacteristic;
                            byte[] bytesPlayTimecode = BitConverter.GetBytes(tc);
                            await gattCharacteristicCommand.WriteValueWithResponseAsync(bytesPlayTimecode);
                        }
                        else
                        {
                            QueryGATT(bd.bluetoothDevice);
                            bd.log = " waiting";
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Error unexpected! Ex[" + ex.Message + "]");
                    }
                }
            }
        }

        public static async void SendMessage(string message)
        {
            foreach (KeyValuePair<string, BleDevice> kvp in bleDevices)
            {
                BleDevice bd = kvp.Value;
                if (bd.bluetoothDevice.Gatt != null)
                {
                    try
                    {
                        if (bd.serviceCache.Count > 0)
                        {
                            GattCharacteristic gattCharacteristicCommand = bd.serviceCache[mainServiceUuid].characteristics[mainCommandUuid].gattCharacteristic;
                            byte[] bytesCommand = Encoding.ASCII.GetBytes(message + "\r\n");
                            await gattCharacteristicCommand.WriteValueWithResponseAsync(bytesCommand);
                        }
                        else
                        {
                            QueryGATT(bd.bluetoothDevice);
                            bd.log = " waiting";
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Error unexpected! Ex[" + ex.Message + "]");
                    }
                }
            }
        }


        public static async void QueryGATT(BluetoothDevice bd)
        {
            BleDevice device = new BleDevice();
            device.name = bd.Name;
            device.id = bd.Id;
            RemoteGattServer rgs = bd.Gatt;
            Console.WriteLine("BD " + bd.Name + " = " + bd.Id + ", gatt = " + bd.Gatt.ToString());

            List<GattService> gattServices = await rgs.GetPrimaryServicesAsync();
            foreach (GattService gattService in gattServices)
            {
                BleCacheService service = new BleCacheService();
                service.uuid = gattService.Uuid;
                service.gattService = gattService;

                Console.WriteLine("Gatt Service : " + gattService.Uuid);
                var characteristics = await gattService.GetCharacteristicsAsync();
                foreach (GattCharacteristic gattCharacteristic in characteristics)
                {
                    BleCacheCharacteristic characteristic = new BleCacheCharacteristic();
                    Console.WriteLine("GattCharacteristic: " + gattCharacteristic.Uuid);
                    characteristic.uuid = gattCharacteristic.Uuid;
                    characteristic.gattCharacteristic = gattCharacteristic;
                    service.characteristics[characteristic.uuid] = characteristic;
                }
                device.serviceCache[service.uuid] = service;//.Add(service);
            }
            device.bluetoothDevice = bd;
            bleDevices[device.name] = device;
        }

        public static async Task<bool> DiscoverDevicesAsync()
        {
            var discoveredDevices = await Bluetooth.ScanForDevicesAsync();
            Console.WriteLine($"found {discoveredDevices?.Count} devices");

            foreach (BluetoothDevice bd in discoveredDevices)
            {
                if (bd.Name.Contains("LightSuit"))
                {
                    //QueryGATT(bd);
                }
                else Console.WriteLine("Ignoring:" + bd.Name);
            }

            return false;
        }


        private static async void Bluetooth_AdvertisementReceived(object sender, BluetoothAdvertisingEvent e)
        {
            MonitorLog += " (BT)" + e.Name+ "\n";

            /*if (e.Name == "MY_DEVICE_NAME")
            {
                await e.Device.Gatt.ConnectAsync();
                var servs = await e.Device.Gatt.GetPrimaryServicesAsync();
            }*/
        }

        static public Thread listenerThread = null;
        static public bool keepListening = true;
        static public string MonitorLog = "";
        static private void ListenToConnected(object in_name)
        {
            //Bluetooth.AdvertisementReceived += Bluetooth_AdvertisementReceived;
            //bluetoothLEScan = await Bluetooth.RequestLEScanAsync();
            //var t = Task.Run( () => Bluetooth.RequestLEScanAsync() );
            //t.Wait();

            while (keepListening)
            {
                //var t = Task.Run( () => Bluetooth.RequestLEScanAsync() );
                //t.Wait();
                //BluetoothLEScan bluetoothLEScan = t.Result;

                var t = Task.Run( () => Bluetooth.ScanForDevicesAsync() );
                var discoveredDevices = t.Result;
                MonitorLog = "Inactive BLE Devices:\n";

                //Console.WriteLine($"found {discoveredDevices?.Count} devices");

                foreach (BluetoothDevice bd in discoveredDevices)
                {
                    MonitorLog += " " + bd.Id + " : " + bd.Name + "\n";
                }





                //MonitorLog += String.Format($"{discoveredDevices?.Count} devices\n");

                /*foreach (BluetoothDevice bd in discoveredDevices)
                {
                    MonitorLog += " (ble)" + bd.Name + "\n";                    
                }*/


                Thread.Sleep(1);
            }
        }


        public static void StartMonitoring()
        {
            listenerThread = new Thread(ListenToConnected);// new ThreadStart(ListenToConnected));
            listenerThread.Start("FindBLE");
            MonitorLog = "Searching for BLE nearby..\n";
        }

        public static void StopMonitoring()
        {
            keepListening = false;
        }
    }
}
