//Pairing at? https://github.com/Rogeriohsjr/BlueToothArduino/blob/master/BlueTooth_Connector_Arduino/Form1.cs
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using System;
using System.Collections.Generic;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
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
using System.Threading;
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
        static TextBox _leaderWindow;
        static TextBox _followWindow;
        static BluetoothClient bluetoothClient;
        static public Dictionary<string, BluetoothDeviceInfo> pairedBluetoothDevices = new Dictionary<string, BluetoothDeviceInfo>();
        static public Dictionary<string, BluetoothClient> pairedBluetoothConnections = new Dictionary<string, BluetoothClient>();
        static public string _followText = "";
        static public string _leaderText = "";
        static public Thread listenerThreadLeader;
        static public Thread listenerThreadFollow;

        static public void SendMessage(string name, string pMessage)
        {
            if (!pairedBluetoothConnections.ContainsKey(name))
                return;

            try
            {

                Console.WriteLine("Sending..");
                Stream peerStream = pairedBluetoothConnections[name].GetStream();
                byte[] bMessage = System.Text.Encoding.ASCII.GetBytes(pMessage);
                peerStream.Write(bMessage, 0, bMessage.Length);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error unexpected! Ex[" + ex.Message + "]");
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
            }
            catch (Exception ex)
            {
                pairedBluetoothConnections.Remove(name);
                Console.WriteLine("Error connecting : " + ex);
                return;
            }
            Console.WriteLine(" - Connected");

            threadsActive = true;

            listenerThreadLeader = new Thread(new ThreadStart(ListenToConnectedLeader));
            listenerThreadLeader.Start();

            listenerThreadFollow = new Thread(new ThreadStart(ListenToConnectedFollow));
            listenerThreadFollow.Start();

            _Go = true;

        }

        static public void FindPaired(string LeaderName, string FollowName)
        {
            foreach (BluetoothDeviceInfo di in bluetoothClient.PairedDevices)
            {
                Console.WriteLine("Device : " + di.DeviceAddress.ToString());
                if (di.DeviceName == LeaderName)
                {
                    Connect(LeaderName, di);
                }
                if (di.DeviceName == FollowName)
                {
                    Connect(FollowName, di);
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
            pairedBluetoothConnections.Remove("Leader");
            pairedBluetoothConnections.Remove("Led Follow");

            bluetoothClient.Close();
            _Go = false;
            threadsActive = false;
        }

        static private void ListenToConnectedLeader()
        {
            while (threadsActive)
            {
                while (_Go)
                {
                    if (pairedBluetoothConnections.ContainsKey("Leader"))
                    {
                        Stream s = pairedBluetoothConnections["Leader"].GetStream();
                        if (!pairedBluetoothConnections["Leader"].Connected) { return; }

                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            _leaderText += value + "\n";
                        }
                        catch (Exception ex)
                        {
                        }
                    }
                }
            }
        }

        static private void ListenToConnectedFollow()
        {
            while (threadsActive)
            {
                while (_Go)
                {
                    if (pairedBluetoothConnections.ContainsKey("Led Follow"))
                    {
                        Stream s = pairedBluetoothConnections["Led Follow"].GetStream();
                        if (!pairedBluetoothConnections["Led Follow"].Connected) { return; }

                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                           _followText += value + "\n";
                        }
                        catch (Exception ex)
                        {
                        }
                    }
                }
            }
        }


        static Thread _ListenToConnected;
        static BluetoothListener _Listener;
        static public void Initialize(TextBox leaderWindow, TextBox followWindow)
        {
            _leaderWindow = leaderWindow;
            _followWindow = followWindow;
            bluetoothClient = new BluetoothClient();
//            _Listener = new BluetoothListener(BluetoothService.SerialPort);
            //_Listener.Start();
        }
    }
}
