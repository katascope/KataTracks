//Pairing at? https://github.com/Rogeriohsjr/BlueToothArduino/blob/master/BlueTooth_Connector_Arduino/Form1.cs
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Media;
//using System.Windows.Forms;
using NAudio;
using NAudio.Wave;
using NAudio.MediaFoundation;
using NAudio.FileFormats;
using System.Windows.Threading;
using System.Windows.Controls.Primitives;

namespace KataTracks
{
    public class CombinedBluetoothController
    {
        static bool _Go;
        static bool threadsActive = false;
        static BluetoothClient bluetoothClient;
        static public Dictionary<string, BluetoothDeviceInfo> pairedBluetoothDevices = new Dictionary<string, BluetoothDeviceInfo>();
        static public Dictionary<string, BluetoothClient> pairedBluetoothConnections = new Dictionary<string, BluetoothClient>();
        static public Dictionary<string, string> Logs = new Dictionary<string, string>();
        static public Dictionary<string, Thread> listenerThreads = new Dictionary<string, Thread>();

        static public void SendMessage(string pMessage)
        {
            foreach (KeyValuePair<string, BluetoothClient> clients in pairedBluetoothConnections)
            {
                try
                {
                    Console.WriteLine("Sending..");
                    Stream peerStream = pairedBluetoothConnections[clients.Key].GetStream();
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

        static private void ListenToConnected(object in_name)
        {
            
            while (threadsActive)
            {
                while (_Go)
                {
                    string name = (string)in_name;
                    if (pairedBluetoothConnections.ContainsKey(name))
                    {
                        Stream s = pairedBluetoothConnections[name].GetStream();
                        if (!pairedBluetoothConnections[name].Connected) { return; }

                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            Logs[name] += value + "\n";
                        }
                        catch (Exception ex)
                        {
                            Logs[name] += ex.ToString();
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
                pairedBluetoothConnections[name] = new BluetoothClient();
                pairedBluetoothConnections[name].Connect(di.DeviceAddress, BluetoothService.SerialPort);
                pairedBluetoothDevices[name] = di;
                Logs[name] = "Ready.";
            }
            catch (Exception ex)
            {
                pairedBluetoothConnections.Remove(name);
                Console.WriteLine("Error connecting : " + ex);
                return;
            }
            Console.WriteLine(" - Connected");

            threadsActive = true;


            listenerThreads[name] = new Thread(ListenToConnected);// new ThreadStart(ListenToConnected));
            listenerThreads[name].Start(name);


            _Go = true;

        }

        static public void FindPaired(string searchName)
        {
            foreach (BluetoothDeviceInfo di in bluetoothClient.PairedDevices)
            {
                Console.WriteLine("Paired : " + di.DeviceAddress.ToString());
                if (di.DeviceName.Contains(searchName))
                {
                    pairedBluetoothDevices[di.DeviceName] = di;
                }
            }
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


        static public bool IsOnline(string name)
        {
            if (pairedBluetoothConnections.ContainsKey(name) && pairedBluetoothConnections[name] != null)
                return true;
            return false;
        }

        static public void Close()
        {
            foreach (KeyValuePair<string, BluetoothClient> kvp in pairedBluetoothConnections)
            {
                pairedBluetoothConnections[kvp.Key].Close();
                pairedBluetoothConnections[kvp.Key].Dispose();
            }
            pairedBluetoothConnections.Remove("Lightsuit1");
            pairedBluetoothConnections.Remove("Lightsuit2");

            bluetoothClient.Close();
            _Go = false;
            threadsActive = false;
        }
        /*
        static private void ListenToConnected1()
        {
            while (threadsActive)
            {
                while (_Go)
                {
                    if (pairedBluetoothConnections.ContainsKey("Lightsuit1"))
                    {
                        Stream s = pairedBluetoothConnections["Lightsuit1"].GetStream();
                        if (!pairedBluetoothConnections["Lightsuit1"].Connected) { return; }

                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            _Log1 += value + "\n";
                        }
                        catch (Exception ex)
                        {
                        }
                    }
                }
            }
        }

        static private void ListenToConnected2()
        {
            while (threadsActive)
            {
                while (_Go)
                {
                    if (pairedBluetoothConnections.ContainsKey("Lightsuit2"))
                    {
                        Stream s = pairedBluetoothConnections["Lightsuit2"].GetStream();
                        if (!pairedBluetoothConnections["Lightsuit2"].Connected) { return; }

                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            _Log2 += value + "\n";
                        }
                        catch (Exception ex)
                        {
                        }
                    }
                }
            }
        }
        */

        static public void Initialize()
        {
            bluetoothClient = new BluetoothClient();
        }
    }
}
