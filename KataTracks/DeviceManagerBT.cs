using System;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace KataTracks
{
    public class DeviceManagerBT
    {
        static public Thread monitorThread = null;
        static public bool keepListening = true;
        public static Dictionary<string, string> discoveredBT = new Dictionary<string, string>();
        public static Dictionary<string, string> clientNames = new Dictionary<string, string>();
        public static Dictionary<string, BluetoothClient> clients = new Dictionary<string, BluetoothClient>();
        public static Dictionary<string, Thread> clientThreads = new Dictionary<string, Thread>();
        public static Dictionary<string, string> clientLogs = new Dictionary<string, string>();
        static public string MonitorLog = "";
        static public string DiscoveryLog = "";

        public static void SendMessage(string message)
        {
            foreach (KeyValuePair<string, BluetoothClient> kvp in DeviceManagerBT.clients)
            {
                if (kvp.Value.Connected)
                {
                    try
                    {
                        Stream peerStream = kvp.Value.GetStream();
                        if (peerStream != null)
                        {
                            byte[] msg = System.Text.Encoding.ASCII.GetBytes(message);
                            peerStream.Write(msg, 0, msg.Length);
                            //peerStream.Flush();
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Error unexpected! Ex[" + ex.Message + "]");
                    }
                }
            }
        }


        static private void ListenToConnected(object in_name)
        {
            while (keepListening)
            {
                string deviceName = (string)in_name;

                if (clients.ContainsKey(deviceName) && clients[deviceName].Connected)
                {
                    BluetoothClient client = clients[deviceName];
                    
                    clientLogs[deviceName] = deviceName + " connected (BT)\n";
                    Stream s = clients[deviceName].GetStream();
                    if (clients[deviceName].Connected)
                    {
                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            clientLogs[deviceName] += " Status=" + value + "\n";
                        }
                        catch (Exception ex)
                        {
                            clientLogs[deviceName] += ex.ToString();
                        }
                    }
                }
                        
                Thread.Sleep(1000); //don't check again for 5 seconds
            }
        }

        static public string[] DiscoverPaired()
        {
            BluetoothClient client = new BluetoothClient();
            var pds = client.PairedDevices;
            DiscoveryLog = "Paired BT Lightsuits:\n";
            discoveredBT = new Dictionary<string, string>();
            List<string> suits = new List<string>();
            foreach (var pd in pds)
            {
                if ((pd.DeviceName.Contains("Lightsuit")) || (pd.DeviceName.Contains("LightSuit")))
                {
                    DiscoveryLog += " + " + pd.DeviceName + " " + pd.DeviceAddress + "\n";
                    discoveredBT[pd.DeviceAddress.ToString()] = pd.DeviceName;
                    suits.Add(pd.DeviceAddress.ToString());
                }
                else DiscoveryLog += " - " + pd.DeviceName + " " + pd.DeviceAddress + "\n";
            }
            return suits.ToArray();
        }

        static private void MonitorBluetoothDevices(object in_name)
        {
            while (keepListening)
            {
                BluetoothClient client = new BluetoothClient();
                var pds = client.PairedDevices;
                string tempLog = "Inactive Paired Devices\n";
                foreach (var pd in pds)
                {
                    if ((pd.DeviceName.Contains("Lightsuit")) || (pd.DeviceName.Contains("LightSuit")))
                    {
                        if (!clients.ContainsKey(pd.DeviceName) || !clients[pd.DeviceName].Connected)
                        {
                            string deviceLog = "";
                            clients[pd.DeviceName] = new BluetoothClient();
                            try
                            {
                                deviceLog += " " + pd.DeviceName + " connecting.\n";
                                clientLogs[pd.DeviceName] = deviceLog;
                                clients[pd.DeviceName].Connect(pd.DeviceAddress, BluetoothService.SerialPort);
                                if (clients[pd.DeviceName].Connected)
                                {
                                    clientThreads[pd.DeviceName] = new Thread(ListenToConnected);
                                    clientThreads[pd.DeviceName].Start(pd.DeviceName);
                                    MonitorLog += "Thread start " + pd.DeviceName + "\n";
                                }

                            }
                            catch (Exception ex)
                            {
                                if (ex.Message.Contains("did not pr"))
                                    deviceLog += " " + pd.DeviceName + " not found";
                                else if (ex.Message.Contains("is not valid"))
                                    deviceLog += " " + pd.DeviceName + " invalid";
                                else
                                    deviceLog += " " + pd.DeviceName + " unk err";
                                deviceLog += ", retrying\n";
                            }
                            clientLogs[pd.DeviceName] = deviceLog;
                            tempLog += deviceLog;
                        }
                        else
                        {
                            //tempLog += "+" + pd.DeviceName + " ??\n";
                        }
                    }
                    else tempLog += "-" + pd.DeviceName + "\n";
                }
                MonitorLog = tempLog;
                Thread.Sleep(5000); //don't check again for 5 seconds
            }
        }

        static private void WatchBluetoothDevice(object in_name)
        {
            InTheHand.Net.BluetoothAddress deviceAddress = (InTheHand.Net.BluetoothAddress)in_name;
            string btAddress = (string)in_name.ToString();
            while (keepListening)
            {
                BluetoothClient client = clients[btAddress];
                string deviceName = clientNames[btAddress];
                string deviceLog = deviceName + " BT thread(" + clientThreads[btAddress].ManagedThreadId.ToString() + ")\n";
                if (!clients[btAddress].Connected)
                {
                    deviceLog += " " + deviceName + " connecting.\n";
                    try
                    {
                        clients[btAddress].Connect(deviceAddress, BluetoothService.SerialPort); ;
                    }
                    catch (Exception ex)
                    {
                        deviceLog += ex;
                    }
                    if (clients[btAddress].Connected)
                    {
                        deviceLog += " " + deviceName + " connected ok.\n";
                    }
                }
                else
                {
                    deviceLog += " " + deviceName + " is connected.\n";
                    Stream s = clients[btAddress].GetStream();
                    if (clients[btAddress].Connected)
                    {
                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            if (value == null)
                            {
                                //this is a problem
                                clients[btAddress].Dispose();
                                clients[btAddress] = new BluetoothClient();
                            }
                            deviceLog += " Status=" + value + "\n";
                        }
                        catch (Exception ex)
                        {
                            deviceLog += ex.ToString();
                        }
                    }
                }
                clientLogs[btAddress] = deviceLog;
            }
        }

        public async static void EnsureConnection(InTheHand.Net.BluetoothAddress btAddress, string btName)
        {
            string address = (string)btAddress.ToString();
            if (!clients.ContainsKey(address))
            {
                clients[address] = new BluetoothClient();
                clientNames[address] = btName;
                clientThreads[address] = new Thread(WatchBluetoothDevice);
                clientThreads[address].Start(btAddress);
            }
        }

        public async static void StartMonitoring()
        {
            monitorThread = new Thread(MonitorBluetoothDevices);
            monitorThread.Start("FindBT");
            MonitorLog = "Searching BLE Nearby..\n";
        }

        public static void StopMonitoring()
        {
            keepListening = false;
        }
    }
}
 