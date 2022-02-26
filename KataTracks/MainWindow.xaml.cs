using System;
using System.Collections.Generic;
//using InTheHand.Net.Bluetooth;
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
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        static string filename = "..\\..\\..\\TronGame.m4a";
        static string bluetoothDeviceSearchName = "Lightsuit";
        static WaveOutEvent outputDevice = null;
        static DispatcherTimer animationTimer;
        static DispatcherTimer connectionTimer;
        static DispatcherTimer btTextTimer;
        static bool playing = false;
        static DateTime literalTrackStartTime;
        float volume = 0.15f;
        static long timePick = 0;
        static bool b1Down = false;
        static ulong textTickCount = 0;
        static Thread discoverBleThread;
        static Dictionary<string, string> foundDevices = null;
        public MainWindow()
        {
            InitializeComponent();
            outputDevice = new WaveOutEvent();
            animationTimer = new DispatcherTimer();
            connectionTimer = new DispatcherTimer();
            btTextTimer = new DispatcherTimer();
            Canvas.SetLeft(TrackIndex, 0);
            Canvas.SetLeft(TrackIndexPlay, 0);
            VolumeSlider.Value = volume;

            MainLog.Text = "KataTracks initializing\n";
            //CombinedBluetoothController.Initialize();

            DeviceWatcher.StartMonitoring();

            //ConnectPaired();

            MainLog.Text += "Ready to Connect\n";

            animationTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            animationTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            animationTimer.Start();

            btTextTimer.Tick += new EventHandler(btTextTimer_Tick);
            btTextTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            btTextTimer.Start();
        }

        private void PlayTrack(int seconds)
        {
            if (playing)
                return;

            MainLog.Text += "Playing Track @" + seconds + " seconds\n";

            var audioFile = new AudioFileReader(filename);

            audioFile.Skip((int)(seconds));
            outputDevice.Init(audioFile);

            string code = "@" + (timePick * 100) + "\r\n";
            //CombinedBluetoothController.SendMessage(code);
            DeviceManagerBT.SendMessage(code);
            DeviceManagerBLE.Play((ulong)timePick * 100);

            outputDevice.Play();
            outputDevice.Volume = volume;
            literalTrackStartTime = DateTime.Now;
            playing = true;
        }

        private void StopTrack(bool resetLocation)
        {
            MainLog.Text += "Stopping track\n";

            outputDevice.Stop();
            //dispatcherTimer.Stop();
            playing = false;
            if (resetLocation)
            {
                Canvas.SetLeft(TrackIndexPlay, 0);
            }
            DeviceManagerBT.SendMessage("(");
            DeviceManagerBLE.SendMessage("(");
        }

        private void WriteLogSlot(int slot, string title, string message)
        {
            switch (slot)
            {
                case 0:
                    Log1Label.Content = title;
                    Log1.Text = message;
                    Log1.ScrollToEnd();
                    break;
                case 1:
                    Log2Label.Content = title;
                    Log2.Text = message;
                    Log2.ScrollToEnd();
                    break;
                case 2:
                    Log3Label.Content = title;
                    Log3.Text = message;
                    Log3.ScrollToEnd();
                    break;
                case 3:
                    Log4Label.Content = title;
                    Log4.Text = message;
                    Log4.ScrollToEnd();
                    break;
            }                
        }

        private void btTextTimer_Tick(object sender, EventArgs e)
        {
            //DeviceManagerBLE.poll();

            int slot = 0;
            foreach (KeyValuePair<string,BleDevice> kvp in DeviceManagerBLE.bleDevices)
            {
                WriteLogSlot(slot, kvp.Value.name, DeviceManagerBLE.bleDevices[kvp.Key].log);
                slot++;
            }

            foreach (KeyValuePair<string, BluetoothClient> kvp in DeviceManagerBT.clients)
            {
                if (kvp.Value.Connected)
                {
                    WriteLogSlot(slot, DeviceManagerBT.clientNames[kvp.Key], DeviceManagerBT.clientLogs[kvp.Key]);
                    slot++;
                }
            }

            textTickCount++;
            MainLog.Text = "Update #" + textTickCount + "\n";
            MainLog.Text += "Actives:\n";
            foreach (KeyValuePair<string, BleDevice> kvp in DeviceManagerBLE.bleDevices)
                MainLog.Text += " " + kvp.Value.log + "\n";

            foreach (KeyValuePair<string, BluetoothClient> kvp in DeviceManagerBT.clients)
            {
                if (kvp.Value.Connected)
                    MainLog.Text += " (BT) " + kvp.Key + " ok\n";
                else if (kvp.Value.Connected)
                    MainLog.Text += " (BT) " + kvp.Key + " NOT ok\n";
            }
            MainLog.Text += "\n";
            MainLog.Text += DeviceManagerBLE.MonitorLog;
            MainLog.ScrollToEnd();

            //Upperview
            BTScannerView.Text = DeviceWatcher.btMonitorLog;
            foreach (KeyValuePair<string, string> kvp in DeviceManagerBT.discoveredBT)
                BTScannerView.Text += kvp.Value + " d/c\n";

            if (foundDevices!= null)
            {
                BleScannerView.Text = "Found: " + foundDevices.Count + "\n";
                foreach (KeyValuePair<string, string> kvp in foundDevices)
                    BleScannerView.Text += kvp.Value + "\n";
            }
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            if (!playing) BluetoothStatus.Content = "Stopped";
            else BluetoothStatus.Content = "Playing";

            if (!playing) return;

            if (outputDevice.PlaybackState == PlaybackState.Stopped)
                StopTrack(true);

            //4,416,049
            TimeSpan timeElapsedSincePlay = DateTime.Now - literalTrackStartTime;// + new TimeSpan(0,0,0,0,(int)timePlay*100);
            TimeSpan timeCurrentInSong = timeElapsedSincePlay + new TimeSpan(0, 0, 0, 0, (int)timePick * 100);
            TrackTime.Content = ""
                + timeCurrentInSong.Minutes + ":"
                + timeCurrentInSong.Seconds + ":"
                + timeCurrentInSong.Milliseconds / 100;

            double timeValue = (double)(timeCurrentInSong.TotalMilliseconds) / 100;
            Canvas.SetLeft(TrackIndexPlay, Math.Round(timeValue, 0));
            CommandManager.InvalidateRequerySuggested();
        }

        private void Exit(object sender, RoutedEventArgs e)
        {
            //DeviceManagerBLE.StopMonitoring();
            DeviceManagerBLE.DisconnectAll();
            DeviceManagerBT.StopMonitoring();
            //DeviceManagerBT.DisconnectAll();
            MainLog.Text += "Exiting\n";
            System.Windows.Application.Current.Shutdown();
            Environment.Exit(0);
        }

        private void ConnectButton_Click(object sender, RoutedEventArgs e)
        {
            DeviceWatcher.StartMonitoring();
        }

        private static void DiscoverBleThread(object in_name)
        {
            foundDevices = DeviceSearchBLE.DiscoverDevicesAsync().Result;
        }

        private void BleSearchButton_Click(object sender, RoutedEventArgs e)
        {
            BleScannerView.Text = "Scanning..\n";
            discoverBleThread = new Thread(DiscoverBleThread);
            discoverBleThread.Start(BleScannerView);
        }

        private void PlayFromStartButton_Click(object sender, RoutedEventArgs e)
        {
            Canvas.SetLeft(TrackIndex, 0);
            timePick = 0;
            Canvas.SetLeft(TrackIndexPlay, timePick);

            TrackTime.Content = "0:0:0";
            TrackTimeOffset.Content = "0:0:0";

            PlayTrack(0);
        }

        private void PlayButton_Click(object sender, RoutedEventArgs e)
        {
            double ts = timePick;
            ts = Math.Round(ts / 10, 0);
            PlayTrack((int)ts);
        }
        private void StopButton_Click(object sender, RoutedEventArgs e)
        {
            Canvas.SetLeft(TrackIndexPlay, 0);
            StopTrack(true);
        }

        private void OnMouseDown(object sender, MouseEventArgs e)
        {
            if (playing)
                return;
            b1Down = true;
        }
        private void OnMouseUp(object sender, MouseEventArgs e)
        {
            b1Down = false;
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            if (b1Down)
            {
                double X = e.GetPosition(this).X;
                timePick = (long)X;

                X = Math.Round(X / 10, 0) * 10;
                Canvas.SetLeft(TrackIndex, X);

                TimeSpan ts = new TimeSpan(0, 0, 0, 0, (int)timePick * 100);// DateTime.Now - trackStartTime;
                TrackTimeOffset.Content = ""
                    + ts.Minutes + ":"
                    + ts.Seconds + ":"
                    + 0;
            }
        }

        private void VolumeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            volume = (float)e.NewValue;
            outputDevice.Volume = volume;
        }

        void StopAndSendToBoth(string value)
        {
            DeviceManagerBLE.SendMessage(value);
            DeviceManagerBT.SendMessage(value);
        }
        private void SendBoth(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;            
            StopAndSendToBoth(""+button.Tag);
        }
        private void SendBothCRLF(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;
            StopAndSendToBoth("" + button.Tag + "\r\n");
        }
    }
}
