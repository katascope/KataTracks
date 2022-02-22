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

/*
 * API Design:
 *   00001800-0000-1000-8000-00805f9b34fb : Generic Access
 *    00002a00-0000-1000-8000-00805f9b34fb : Device Name
 *    00002a01-0000-1000-8000-00805f9b34fb : Appearance
 *   00001801-0000-1000-8000-00805f9b34fb : Generic Attribute
 *    00002a05-0000-1000-8000-00805f9b34fb : Service Changed
 *   9a48ecba-2e92-082f-c079-9e75aae428b1 : LightSuit API
 *    00002713-0000-1000-8000-00805f9b34fb :(rn) Acceleration
 *    1a3ac130-31ee-758a-bc50-54a61958ef81 :(rn) Counter
 *    fe4e19ff-b132-0099-5e94-3ffb2cf07940 :(w) Reset Counter
 *   Add
 *    TimeCode : RWN
 *    PlayCode [State][PalVel][PalDir]
 *    PlayState
 *    Palette Speed
 *    Palette Direction
 *    Maybe Palette (32 bytes)
 *    PlayFromStart, PlayAt, PlayStop
 *    
 *   
 Bluetooth Name:LightSuitA
Bluetooth Name:LightSuitA
Bluetooth DeviceId:BluetoothLE#BluetoothLE00:1a:7d:da:71:11-fd:b8:57:fe:7c:3d
 Service:02fe4875-5056-48b5-ad15-36e30665d9b4
Service fetch start
Service fetch done
 Service:02fe4875-5056-48b5-ad15-36e30665d9b4
  Characteristic:4c75bb42-5365-458d-a3ea-2b91339646b7 - Start thing
   Write
  Characteristic:10365297-362d-44fb-8807-a6aa13b1bd83
   Read:
   Notify
  Characteristic:d01c9106-91bd-4998-9554-85264d33acb2
   Write
   Read:
   Notify
  Characteristic:220154bf-1dce-4f03-85f0-7ba905d2d6b0
   Write
Advertisement:
  BT_ADDR: 278968192105533
  FR_NAME: LightSuitA
*   
 */

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
        public static Dictionary<string, BLEDevice> devices = new Dictionary<string, BLEDevice>();
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

        async static void DoDirectConnections()
        {
            await ConnectDevice(166213468539006);

            DisconnectDevices();
            Thread.Sleep(1000);
        }




        static void DisconnectDevices()
        {
            foreach (KeyValuePair<string, BLEDevice> device in devices)
            {
                Console.WriteLine("Disconnecting device: " + device.Key);

                devices[device.Key].device.Dispose();
            }
        }

        async void ConnectDeviceOld(ulong bluetoothDeviceId)
        {
            BLEDevice bled = new BLEDevice();

            // Note: BluetoothLEDevice.FromIdAsync must be called from a UI thread because it may prompt for consent.
            //BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);
            bled.device = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);
            Console.WriteLine("Bluetooth Name:" + bled.device.Name);
            devices[bled.device.Name] = bled;
            Console.WriteLine("Bluetooth DeviceId:" + bled.device.DeviceId);


            bled.servicesResult = await bled.device.GetGattServicesAsync();
            if (bled.servicesResult.Status == GattCommunicationStatus.Success)
            {
                foreach (GattDeviceService service in bled.servicesResult.Services)
                    Console.WriteLine(" Service:" + service.Uuid);

                Console.WriteLine("Service fetch start");
                var services = bled.servicesResult.Services;
                Console.WriteLine("Service fetch done");

                foreach (GattDeviceService service in services)
                {
                    Console.WriteLine(" Service:" + service.Uuid);
                    GattCharacteristicsResult cresult = await service.GetCharacteristicsAsync();

                    if (cresult.Status == GattCommunicationStatus.Success)
                    {
                        var characteristics = cresult.Characteristics;
                        foreach (GattCharacteristic characteristic in characteristics)
                        {
                            Console.WriteLine("  Characteristic:" + characteristic.Uuid);
                            GattCharacteristicProperties properties = characteristic.CharacteristicProperties;

                            //First service
                            //Name
                            //Appearance 
                            if (properties.HasFlag(GattCharacteristicProperties.Write))
                            {
                                Console.WriteLine("   Write");
                                var writer = new DataWriter();
                                // WriteByte used for simplicity. Other common functions - WriteInt16 and WriteSingle
                                /*                                writer.WriteByte(0x01);

                                                                GattCommunicationStatus wresult = await characteristic.WriteValueAsync(writer.DetachBuffer());
                                                                if (wresult == GattCommunicationStatus.Success)
                                                                {
                                                                    // Successfully wrote to device
                                                                    Console.WriteLine("Wresult:" + wresult);
                                                                }*/
                            }
                            if (properties.HasFlag(GattCharacteristicProperties.Read))
                            {
                                Console.WriteLine("   Read: ");
                                if (characteristic.Uuid.ToString() == "00002a00-0000-1000-8000-00805f9b34fb")// "00002713 -0000-1000-8000-00805f9b34fb")
                                {
                                    while (true)
                                    {
                                        GattReadResult rr = await characteristic.ReadValueAsync();
                                        if (rr.Status == GattCommunicationStatus.Success)
                                        {
                                            Console.Write("   Read: ");
                                            var reader = DataReader.FromBuffer(rr.Value);
                                            uint len = reader.UnconsumedBufferLength;
                                            byte[] input = new byte[reader.UnconsumedBufferLength];
                                            reader.ReadBytes(input);
                                            for (uint i = 0; i < len; i++)
                                            {
                                                Console.Write((char)input[i]);
                                            }
                                            Console.Write(" ");
                                            Console.WriteLine();
                                        }
                                        Thread.Sleep(500);
                                    }
                                }
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
        }

        async void ReadBle(GattCharacteristic gattCharacteristic)
        {
            GattReadResult rr = await gattCharacteristic.ReadValueAsync();
            if (rr.Status == GattCommunicationStatus.Success)
            {
                Console.Write("ReadBLE = ");
                var reader = DataReader.FromBuffer(rr.Value);
                uint len = reader.UnconsumedBufferLength;
                byte[] input = new byte[reader.UnconsumedBufferLength];
                reader.ReadBytes(input);
                for (uint i = 0; i < len; i++)
                {
                    //                    Console.Write((char)input[i]);
                    Console.Write(String.Format("{0:X}", input[i]));
                    Console.Write(" ");
                    //result += (char)input[i];
                }
                Console.Write(" ");
                Console.WriteLine();
            }
        }

        static float ToFloat(byte[] input)
        {
            byte[] newArray = new[] { input[0], input[1], input[2], input[3] };
            return BitConverter.ToSingle(newArray, 0);
        }

        static void Characteristic_ValueChanged(GattCharacteristic sender,
                                    GattValueChangedEventArgs args)
        {
            // An Indicate or Notify reported that the value has changed.
            var reader = DataReader.FromBuffer(args.CharacteristicValue);
            //int value = reader.read();
            //Console.WriteLine("Value: " + value);

            // Parse the data however required.
            uint len = reader.UnconsumedBufferLength;
            byte[] input = new byte[reader.UnconsumedBufferLength];
            reader.ReadBytes(input);

            Console.WriteLine("Val:" + ToFloat(input));
            /*for (uint i = 0; i < len; i++)
            {
                //                    Console.Write((char)input[i]);
                Console.Write(String.Format("{0:X}", input[i]));
                Console.Write(" ");
                //result += (char)input[i];
            }
            Console.Write(" ");
            Console.WriteLine();*/
        }


        static async Task ConnectDevice(ulong bluetoothDeviceId)
        {
            using (BLEDevice bled = new BLEDevice())
            {

                // Note: BluetoothLEDevice.FromIdAsync must be called from a UI thread because it may prompt for consent.
                //BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);

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
                    /*
                    //GattCharacteristic gcName = bled.GetCharacteristic("00001800-0000-1000-8000-00805f9b34fb", "1a3ac130-31ee-758a-bc50-54a61958ef81"); 
                    GattCharacteristic gcAccel= bled.GetCharacteristic("9a48ecba-2e92-082f-c079-9e75aae428b1", "00002713-0000-1000-8000-00805f9b34fb");
                    //while (true)                    ReadBle(gcName);

                    GattCommunicationStatus status = await gcAccel.WriteClientCharacteristicConfigurationDescriptorAsync(
                            GattClientCharacteristicConfigurationDescriptorValue.Notify);
                    if (status == GattCommunicationStatus.Success)
                    {
                        // Server has been informed of clients interest.
                        gcAccel.ValueChanged += Characteristic_ValueChanged;
                    }
                    */
                }
                else if (bled.servicesResult.Status == GattCommunicationStatus.Unreachable)
                {
                    Console.WriteLine("Remote device unreachable");
                }
                else Console.WriteLine("Failed");
            }
            
        }

        static bool inProcess = false;

        private static void OnAdvertisementReceived(BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs)
        {

            if (eventArgs.Advertisement.LocalName.Contains("LightSuitB"))
            {
                Console.WriteLine(String.Format("Found:" + eventArgs.Advertisement.LocalName + " / " + eventArgs.Advertisement.ServiceUuids.ToString()));
                if (!inProcess)
                {
                    inProcess = true;
                    // Tell the user we see an advertisement and print some properties
                    log += String.Format("Advertisement:");
                    log += String.Format("  BT_ADDR: {0}", eventArgs.BluetoothAddress);
                    log += String.Format("  FR_NAME: {0}", eventArgs.Advertisement.LocalName) + "\n";
                    
                    ConnectDevice(eventArgs.BluetoothAddress);
                    inProcess = false;
                }
            }
//            else Console.WriteLine(String.Format("Skipping:" + eventArgs.Advertisement.LocalName + " / " + eventArgs.Advertisement.ServiceUuids.ToString()));
        }

    }
}
