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

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            // Start the program
            var program = new Program();

            // Close on key press
            Console.ReadLine();
        }


        class BLEDevice
        {
            public BluetoothLEDevice device;
            public GattDeviceServicesResult servicesResult;

            public Dictionary<string, Dictionary<string, GattCharacteristic>> api = new Dictionary<string, Dictionary<string, GattCharacteristic>>();

            public GattCharacteristic GetCharacteristic(string serviceUuid, string characteristiUuid)
            {
                return api[serviceUuid][characteristiUuid];
            }
        }

        public Program()
        {
            ConnectDevice(166213468539006); 
            return;
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


        async void ConnectDeviceOld(ulong bluetoothDeviceId)
        {
            BLEDevice bled = new BLEDevice();

            // Note: BluetoothLEDevice.FromIdAsync must be called from a UI thread because it may prompt for consent.
            //BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);
            bled.device = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);
            Console.WriteLine("Bluetooth Name:" + bled.device.Name);
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
                    Console.Write(String.Format("{0:X}",input[i]));
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

        void Characteristic_ValueChanged(GattCharacteristic sender,
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


        async void ConnectDevice(ulong bluetoothDeviceId)
        {
            BLEDevice bled = new BLEDevice();

            // Note: BluetoothLEDevice.FromIdAsync must be called from a UI thread because it may prompt for consent.
            //BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);

            bled.device = await BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothDeviceId);
            Console.WriteLine("<<" + bled.device.ConnectionStatus);
            Console.WriteLine("Bluetooth Name:" + bled.device.Name);
            Console.WriteLine("Bluetooth DeviceId:" + bled.device.DeviceId);

            bled.servicesResult = await bled.device.GetGattServicesForUuidAsync(new Guid("9a48ecba-2e92-082f-c079-9e75aae428b1"));
            //bled.servicesResult = await bled.device.GetGattServicesAsync();
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

                while (true)
                {
                    Thread.Sleep(500);
                }


            }
            else if (bled.servicesResult.Status == GattCommunicationStatus.Unreachable)
            {
                Console.WriteLine("Remote device unreachable");
            }
            else Console.WriteLine("Failed");

        }

        static bool inProcess = false;

        private void OnAdvertisementReceived(BluetoothLEAdvertisementWatcher watcher, BluetoothLEAdvertisementReceivedEventArgs eventArgs)
        {
            if (eventArgs.Advertisement.LocalName.Contains("LightSuit"))
            {
                if (!inProcess)
                {
                    inProcess = true;
                    // Tell the user we see an advertisement and print some properties
                    Console.WriteLine(String.Format("Advertisement:"));
                    Console.WriteLine(String.Format("  BT_ADDR: {0}", eventArgs.BluetoothAddress));
                    Console.WriteLine(String.Format("  FR_NAME: {0}", eventArgs.Advertisement.LocalName));
                    Console.WriteLine();
                    ConnectDevice(eventArgs.BluetoothAddress);
                    inProcess = false;
                }
            }
            //else Console.WriteLine(String.Format("Skipping:" + eventArgs.Advertisement.LocalName));
        }
    }
}
