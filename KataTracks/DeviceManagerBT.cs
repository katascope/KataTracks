using System;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace KataTracks
{
    class DeviceManagerBT
    {
        static public Thread listenerThread = null;
        static public bool keepListening = true;
        static public string MonitorLog = "";

        public static Dictionary<string, BluetoothClient> clients = new Dictionary<string, BluetoothClient>();

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
                            byte[] bMessage = System.Text.Encoding.ASCII.GetBytes(message);
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

            static private void ListenToConnected(object in_name)
        {
            while (keepListening)
            {
                BluetoothClient client = new BluetoothClient();
                var pds = client.PairedDevices;
                string tempLog = "Inactive Paired Devices\n";
                foreach (var pd in pds)
                {
                    if ( (pd.DeviceName.Contains("Lightsuit")) || (pd.DeviceName.Contains("LightSuit")))
                    {
                        if ( !clients.ContainsKey(pd.DeviceName) || !clients[pd.DeviceName].Connected)
                        {
                            clients[pd.DeviceName] = new BluetoothClient();
                            try
                            {
                                clients[pd.DeviceName].Connect(pd.DeviceAddress, BluetoothService.SerialPort);
                                tempLog += " " + pd.DeviceName + " connecting.\n";
                            }
                            catch (Exception ex)
                            {
                                if (ex.Message.Contains("did not pr"))
                                    tempLog += " " + pd.DeviceName + " not found"; 
                                else if (ex.Message.Contains("is not valid"))
                                    tempLog += " " + pd.DeviceName + " invalid";
                                else
                                    tempLog += " " + pd.DeviceName + " unk err";
                                tempLog += ", retrying\n";
                            }
                        }
                        else tempLog += "+" + pd.DeviceName + " ok\n";
                    }
                    else tempLog += "-" + pd.DeviceName + "\n";
                }
                MonitorLog = tempLog;
                Thread.Sleep(5000); //don't check again for 5 seconds
            }
        }


        public async static void StartMonitoring()
        {
            listenerThread = new Thread(ListenToConnected);
            listenerThread.Start("FindBT");
            MonitorLog = "Searching BLE Nearby..\n";
        }

        public static void StopMonitoring()
        {
            keepListening = false;
        }
    }
}
 