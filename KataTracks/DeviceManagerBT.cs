using System;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace KataTracks
{
    class DeviceManagerBT
    {
        static public Thread monitorThread = null;
        static public bool keepListening = true;
        public static Dictionary<string, BluetoothClient> clients = new Dictionary<string, BluetoothClient>();
        public static Dictionary<string, Thread> threads = new Dictionary<string, Thread>();
        public static Dictionary<string, string> clientLogs = new Dictionary<string, string>();
        static public string MonitorLog = "";

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
                    
                    clientLogs[deviceName] = deviceName + " connected\n";
                    Stream s = clients[deviceName].GetStream();
                    if (clients[deviceName].Connected)
                    {
                        StreamReader reader = new StreamReader(s);
                        try
                        {
                            string value = reader.ReadLine();
                            clientLogs[deviceName] += value + "\n";
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
                                    threads[pd.DeviceName] = new Thread(ListenToConnected);
                                    threads[pd.DeviceName].Start(pd.DeviceName);
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
                            clientLogs[pd.DeviceName] = pd.DeviceName + " ??";
                            tempLog += "+" + pd.DeviceName + " ??\n";
                        }
                    }
                    else tempLog += "-" + pd.DeviceName + "\n";
                }
                MonitorLog = tempLog;
                Thread.Sleep(5000); //don't check again for 5 seconds
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
 