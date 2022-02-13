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
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        static string filename = "..\\..\\..\\TronGame.m4a";
        static string bluetoothDeviceSearchName = "Lightsuit";
        static WaveOutEvent outputDevice = null;
        static DispatcherTimer dispatcherTimer;
        static DispatcherTimer btTextTimer;
        static bool playing = false;
        static DateTime literalTrackStartTime;
        float volume = 0.15f;
        static long timePick = 0;
        static bool b1Down = false;
        static Dictionary<int,string> connectionSlots = new Dictionary<int, string>();

        public MainWindow()
        {
            InitializeComponent();
            outputDevice = new WaveOutEvent();
            dispatcherTimer = new DispatcherTimer();
            btTextTimer = new DispatcherTimer();
            Canvas.SetLeft(TrackIndex, 0);
            Canvas.SetLeft(TrackIndexPlay, 0);
            VolumeSlider.Value = volume;

            MainLog.Text = "KataTracks initializing\n";
            CombinedBluetoothController.Initialize();
            MainLog.Text += "Finding '" + bluetoothDeviceSearchName + "'\n";
            CombinedBluetoothController.FindPaired(bluetoothDeviceSearchName);
            foreach (KeyValuePair<string, BluetoothDeviceInfo> kvp in CombinedBluetoothController.pairedBluetoothDevices)
            {
                MainLog.Text += " " + kvp.Key + "\n";// + " " + kvp.Value.DeviceAddress + "\n";
            }

            MainLog.Text += "Connecting..\n";
            CombinedBluetoothController.ConnectPaired("Lightsuit");
            int count = 0;
            foreach (KeyValuePair<string, BluetoothClient> kvp in CombinedBluetoothController.pairedBluetoothConnections)
            {
                MainLog.Text += "+" + kvp.Key + "\n";// + " (" + CombinedBluetoothController.pairedBluetoothDevices[kvp.Key].DeviceAddress + ")\n";
                switch (count)
                {
                    case 0: connectionSlots[0] = kvp.Key; Log1Label.Content = kvp.Key; break;
                    case 1: connectionSlots[1] = kvp.Key; Log2Label.Content = kvp.Key; break;
                    case 2: connectionSlots[2] = kvp.Key; Log3Label.Content = kvp.Key; break;
                    case 3: connectionSlots[3] = kvp.Key; Log4Label.Content = kvp.Key; break;
                }

                count++;
            }

            TrackView.Text = Fx.Get();

            MainLog.Text += "Timer created\n";
            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            dispatcherTimer.Start();

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
            CombinedBluetoothController.SendMessage(code);
            //CombinedBluetoothController.SendMessage(followDeviceName, code);


            //CombinedBluetoothController.SendMessage(followDeviceName, ")");
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
            CombinedBluetoothController.SendMessage("(");
        }

        private void btTextTimer_Tick(object sender, EventArgs e)
        {
            for (int i=0;i<4;i++)
            {
                if (connectionSlots.ContainsKey(i))
                {
                    string name = connectionSlots[i];
                    switch (i)
                    {
                        case 0:
                            Log1.Text = CombinedBluetoothController.Logs[name];
                            Log1.ScrollToEnd();
                            break;
                        case 1:
                            Log2.Text = CombinedBluetoothController.Logs[name];
                            Log2.ScrollToEnd();
                            break;
                        case 2:
                            Log3.Text = CombinedBluetoothController.Logs[name];
                            Log3.ScrollToEnd();
                            break;
                        case 3:
                            Log4.Text = CombinedBluetoothController.Logs[name];
                            Log4.ScrollToEnd();
                            break;
                    }
                }
            }
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            if (!playing) BluetoothStatus.Content = "Stopped";
            else BluetoothStatus.Content = "Playing";

            if (CombinedBluetoothController.IsOnline("Lightsuit1"))
                BluetoothStatus.Content += " L1";
            if (CombinedBluetoothController.IsOnline("Lightsuit2"))
                BluetoothStatus.Content += " L2";

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
            MainLog.Text += "Exiting\n";
            CombinedBluetoothController.Close();
            System.Windows.Application.Current.Shutdown();
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
            CombinedBluetoothController.SendMessage(value);
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
