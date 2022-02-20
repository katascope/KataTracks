//Pairing at? https://github.com/Rogeriohsjr/BlueToothArduino/blob/master/BlueTooth_Connector_Arduino/Form1.cs
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;

namespace KataTracks
{
    public class Lightsuit
    {
        public BluetoothDeviceInfo pairedBluetoothDevice;
        public BluetoothClient pairedBluetoothConnection;
        public string Log = "";
        public Thread listenerThread;
    };

    public class CombinedBluetoothController
    {
        static bool _Go;
        static bool threadsActive = false;
        static BluetoothClient bluetoothClient;
        static public Dictionary<string, Lightsuit> lightsuits = new Dictionary<string, Lightsuit>();

        static private void ListenToConnected(object in_name)
        {
            
            while (threadsActive)
            {
                while (_Go)
                {
                    string name = (string)in_name;
                    if (lightsuits.ContainsKey(name))
                    {
                        Stream s = lightsuits[name].pairedBluetoothConnection.GetStream();
                        if (!lightsuits[name].pairedBluetoothConnection.Connected) { return; }

                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            lightsuits[name].Log += value + "\n";
                        }
                        catch (Exception ex)
                        {
                            lightsuits[name].Log += ex.ToString();
                        }
                    }
                }
            }
        }

        static public void Connect(string name, BluetoothDeviceInfo di)
        {
            Console.Write("Found "+name+" : " + di.DeviceAddress.ToString());
            try
            {
                lightsuits[name] = new Lightsuit();
                lightsuits[name].pairedBluetoothConnection = new BluetoothClient();
                lightsuits[name].pairedBluetoothConnection.Connect(di.DeviceAddress, BluetoothService.SerialPort);
                lightsuits[name].Log = "Ready.";
            }
            catch (Exception ex)
            {
                lightsuits.Remove(name);
                Console.WriteLine("Error connecting : " + ex);
                return;
            }
            Console.WriteLine(" - Connected");

            threadsActive = true; 
            lightsuits[name].listenerThread = new Thread(ListenToConnected);// new ThreadStart(ListenToConnected));
            lightsuits[name].listenerThread.Start(name);
            _Go = true;
        }

        static public Dictionary<string, BluetoothDeviceInfo> FindPaired(string searchName)
        {
            Dictionary<string, BluetoothDeviceInfo> paired = new Dictionary<string, BluetoothDeviceInfo>();
            foreach (BluetoothDeviceInfo di in bluetoothClient.PairedDevices)
            {
                Console.WriteLine("Paired : " + di.DeviceAddress.ToString());
                if (di.DeviceName.Contains(searchName))
                {
                    paired[di.DeviceName] = di;
                }
            }
            return paired;
        }

        static public void ConnectPaired(string searchName)
        {
            foreach (BluetoothDeviceInfo di in bluetoothClient.PairedDevices)
            {
                Console.WriteLine("Connect : " + di.DeviceAddress.ToString());
                if (di.DeviceName.Contains(searchName))
                {
                    Connect(di.DeviceName, di);
                }
            }
        }

        static public void Initialize()
        {
            bluetoothClient = new BluetoothClient();
        }

        static public void Close()
        {
            foreach (KeyValuePair<string, Lightsuit> kvp in lightsuits)
            {
                string name = kvp.Key;
                Lightsuit lightsuit = kvp.Value;
                lightsuit.pairedBluetoothConnection.Close();
                lightsuit.pairedBluetoothConnection.Dispose();
            }
            if (bluetoothClient != null)
                bluetoothClient.Close();
            _Go = false;
            threadsActive = false;
        }

        static public void SendMessage(string pMessage)
        {
            foreach (KeyValuePair<string, Lightsuit> kvp in lightsuits)
            {
                string name = kvp.Key;
                Lightsuit lightsuit = kvp.Value;
                try
                {
                    Console.WriteLine("Sending..");
                    Stream peerStream = lightsuit.pairedBluetoothConnection.GetStream();
                    if (peerStream != null)
                    {
                        byte[] bMessage = System.Text.Encoding.ASCII.GetBytes(pMessage);
                        peerStream.Write(bMessage, 0, bMessage.Length);
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
