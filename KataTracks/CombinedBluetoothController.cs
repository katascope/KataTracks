//Pairing at? https://github.com/Rogeriohsjr/BlueToothArduino/blob/master/BlueTooth_Connector_Arduino/Form1.cs
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

namespace KataTracks
{
    public class CombinedBluetoothController
    {
        static BluetoothClient bluetoothClient;
        static public Dictionary<string, BluetoothDeviceInfo> pairedBluetoothDevices = new Dictionary<string, BluetoothDeviceInfo>();
        static public Dictionary<string, BluetoothClient> pairedBluetoothConnections = new Dictionary<string, BluetoothClient>();
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

        static public void FindPaired(string LeaderName, string FollowName)
        {
            foreach (BluetoothDeviceInfo di in bluetoothClient.PairedDevices)
            {
                Console.WriteLine("Device : " + di.DeviceAddress.ToString());
                if (di.DeviceName == LeaderName)
                {
                    Console.Write("Found Leader : " + di.DeviceAddress.ToString());
                    try
                    {
                        pairedBluetoothConnections[LeaderName] = new BluetoothClient();
                        pairedBluetoothConnections[LeaderName].Connect(di.DeviceAddress, BluetoothService.SerialPort);
                        pairedBluetoothDevices[LeaderName] = di;
                    }
                    catch (Exception ex)
                    {
                        pairedBluetoothConnections.Remove(LeaderName);
                        Console.WriteLine("Error connecting : " + ex);
                        return;
                    }
                    Console.WriteLine(" - Connected");
                }
                if (di.DeviceName == FollowName)
                {
                    Console.Write("Found Follow : " + di.DeviceAddress.ToString());
                    try
                    {
                        pairedBluetoothConnections[FollowName] = new BluetoothClient();
                        pairedBluetoothConnections[FollowName].Connect(di.DeviceAddress, BluetoothService.SerialPort);
                        pairedBluetoothDevices[FollowName] = di;
                    }
                    catch (Exception ex)
                    {
                        pairedBluetoothConnections.Remove(FollowName);
                        Console.WriteLine("Error connecting : " + ex);
                        return;
                    }
                    Console.WriteLine(" - Connected");
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
            bluetoothClient.Close();
        }

        static public void Initialize()
        {
            bluetoothClient = new BluetoothClient();
        }
    }
}
