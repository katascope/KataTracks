﻿//Reading: https://docs.microsoft.com/en-us/dotnet/core/compatibility/interop/5.0/built-in-support-for-winrt-removed
using System;
using System.Text;
using System.Threading;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Collections.Concurrent;
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
        public ConcurrentDictionary<BluetoothUuid, BleCacheCharacteristic> characteristics = new ConcurrentDictionary<BluetoothUuid, BleCacheCharacteristic>();
    }

    public class BleDevice
    {
        public string id;
        public string name;
        public BluetoothDevice bluetoothDevice;
        public ConcurrentDictionary<BluetoothUuid, BleCacheService> serviceCache = new ConcurrentDictionary<BluetoothUuid, BleCacheService>();
        public string log = "";
        public Thread monitorThread;
        public bool stayActive = true;
        public bool queryingGatt = false;
        public ConcurrentQueue<string> sendQueue = new ConcurrentQueue<string>();
    }

    public class DeviceManagerBLE
    {
        public static string MonitorLog = "";
        public static ConcurrentDictionary<string, BleDevice> bleDevices = new ConcurrentDictionary<string, BleDevice>();

        static BluetoothUuid mainServiceUuid = BluetoothUuid.FromGuid(new Guid("02FE4875-5056-48B5-AD15-36E30665D9B4"));
        static BluetoothUuid mainCommandUuid = BluetoothUuid.FromGuid(new Guid("220154BF-1DCE-4F03-85F0-7BA905D2D6B0"));
        static BluetoothUuid mainAuthenticateUuid = BluetoothUuid.FromGuid(new Guid("4C75BB42-5365-458D-A3EA-2B91339646B7"));
        static BluetoothUuid mainTimecodeUuid = BluetoothUuid.FromGuid(new Guid("10365297-362D-44FB-8807-A6AA13B1BD83"));
        static BluetoothUuid mainPlayUuid = BluetoothUuid.FromGuid(new Guid("3B140EF5-0A72-4891-AD38-83B5A2595622"));
        static BluetoothUuid mainStatusUuid = BluetoothUuid.FromGuid(new Guid("D01C9106-91BD-4998-9554-85264D33ACB2"));
        static BluetoothUuid mainCounterUuid = BluetoothUuid.FromGuid(new Guid("612DD356-9632-48CF-A279-935D3D4EF242"));
        static BluetoothUuid mainCounterResetUuid = BluetoothUuid.FromGuid(new Guid("EA7CE01E-808B-4EF3-8735-2A05F1C48DFF"));

        static List<string> connectionList = new List<string>() {
                "FA642247BCCD",
                //"FDB857FE7C3D",
                "CA8E42F29042"
            };
    public static void StartMonitoring(List<string> bleDeviceConnectionList)
        {
            //connectionList = bleDeviceConnectionList;

            foreach (string str in connectionList)
            {
                Console.WriteLine("Devices:" + str);
                bleDevices[str] = new BleDevice();
                bleDevices[str].monitorThread = new Thread(MonitorDevice);// new ThreadStart(ListenToConnected));
                bleDevices[str].monitorThread.Start(""+str);

            }
            MonitorLog = "MonitorBLE started..\n";
        }

        public static async void QueryGATT(string bdid)
        {
            BluetoothDevice bd = null;
            while (bd == null)
                bd = Task.Run(() => BluetoothDevice.FromIdAsync(bdid)).Result;


            BleDevice device = bleDevices[bd.Id];
            device.queryingGatt = true;
            device.name = bd.Name;
            device.id = bd.Id;
            RemoteGattServer rgs = bd.Gatt;
            device.log = "BD " + bd.Name + " = " + bd.Id + "\nQuerying GATT\n";

            List<GattService> gattServices = await rgs.GetPrimaryServicesAsync();
            foreach (GattService gattService in gattServices)
            {
                BleCacheService service = new BleCacheService();
                service.uuid = gattService.Uuid;
                service.gattService = gattService;

                //device.log += "Gatt Service : " + gattService.Uuid + "\n";
                var characteristics = await gattService.GetCharacteristicsAsync();
                foreach (GattCharacteristic gattCharacteristic in characteristics)
                {
                    BleCacheCharacteristic characteristic = new BleCacheCharacteristic();
                    //device.log += "GattCharacteristic: " + gattCharacteristic.Uuid + "\n";
                    characteristic.uuid = gattCharacteristic.Uuid;
                    characteristic.gattCharacteristic = gattCharacteristic;
                    service.characteristics[characteristic.uuid] = characteristic;
                }
                device.serviceCache[service.uuid] = service;//.Add(service);
            }
            device.log = bd.Name + " BLE thread(" + device.monitorThread.ManagedThreadId.ToString() + ")\n";
            device.log += " " + bd.Name + " is connected.\n";
            device.log += " Gatt= " + gattServices.Count + "\n";
            device.bluetoothDevice = bd;
            //bleDevices[device.id] = device;
            device.queryingGatt = false;
        }

        static private void MonitorDevice(object in_name)
        {
            string id = (string)in_name;

            while (!bleDevices.ContainsKey(id) || bleDevices[id].stayActive)
            {
                if (bleDevices.ContainsKey(id) && bleDevices[id].serviceCache.Count == 0)
                {
                    bleDevices[id].log = "Waiting : " + id;
                    try
                    {
                        if (!bleDevices[id].queryingGatt)
                        {
                            bleDevices[id].log = "GattQuery : " + id + " " + bleDevices[id].queryingGatt;
                            Task.Run(() => QueryGATT(id)).Wait();
                        }
                    }
                    catch (Exception ex)
                    {
                        bleDevices[id].log = ex.ToString();
                    }
                }
                else
                {
                    while (bleDevices[id].sendQueue.Count > 0)
                    {
                        string message = "";
                        bleDevices[id].sendQueue.TryDequeue(out message);
                        GattCharacteristic gattCharacteristicCommand = bleDevices[id].serviceCache[mainServiceUuid].characteristics[mainCommandUuid].gattCharacteristic;
                        byte[] bytesCommand = Encoding.ASCII.GetBytes(message + "\r\n");
                        gattCharacteristicCommand.WriteValueWithResponseAsync(bytesCommand);
                    }
                }
            }
          
        }

        public static void DisconnectAll()
        {
            foreach (KeyValuePair<string, BleDevice> kvp in bleDevices)
            {
                kvp.Value.stayActive = false;
            }

            foreach (KeyValuePair<string, BleDevice> kvp in bleDevices)
            {
                BleDevice bd = kvp.Value;
                kvp.Value.stayActive = false;
                if (bd.bluetoothDevice != null)
                    bd.bluetoothDevice.Gatt.Disconnect();
            }
            //bleDevices = new ConcurrentDictionary<string, BleDevice>();
        }




















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

        public static async void poll()
        {
            try
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
                                string logUpdate = kvp.Key + " connected (BLE)\n";
                                GattCharacteristic gattCharacteristicStatus = bd.serviceCache[mainServiceUuid].characteristics[mainStatusUuid].gattCharacteristic;
                                byte[] valuesStatus = await gattCharacteristicStatus.ReadValueAsync();
                                logUpdate += String.Format(" {0}-{1}-{2}", valuesStatus[3], valuesStatus[2], valuesStatus[1]);
                                byte b = valuesStatus[0];
                                int rssi = 255 - b;
                                logUpdate += "(-" + rssi + ")\n";

                                GattCharacteristic gattCharacteristicTimecode = bd.serviceCache[mainServiceUuid].characteristics[mainTimecodeUuid].gattCharacteristic;
                                byte[] valuesTimecode = await gattCharacteristicTimecode.ReadValueAsync();
                                ulong timecode = BitConverter.ToUInt32(valuesTimecode, 0);
                                logUpdate += String.Format("  Timecode={0}", timecode);

                                bd.log = logUpdate;
                            }
                            else
                            {
                                QueryGATT(bd.bluetoothDevice.Id);
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
            catch (Exception ex)
            {
                return;
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
                            QueryGATT(bd.bluetoothDevice.Id);
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
                if (bd.bluetoothDevice != null && bd.bluetoothDevice.Gatt != null)
                {
                    try
                    {
                        if (bd.serviceCache.Count > 0)
                        {
                            kvp.Value.sendQueue.Enqueue(message);
                        }
                        else
                        {
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
    }
}

