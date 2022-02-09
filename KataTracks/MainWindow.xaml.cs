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
        static string leaderDeviceName = "Leader";
        static string followDeviceName = "Led Follow";
        static WaveOutEvent outputDevice = null;
        static DispatcherTimer dispatcherTimer;
        static bool playing = false;
        static DateTime literalTrackStartTime;
        float volume = 0.15f;
        static long timePick = 0;
        static bool b1Down = false;
        

        public MainWindow()
        {
            InitializeComponent();
            outputDevice = new WaveOutEvent();
            dispatcherTimer = new DispatcherTimer();
            Canvas.SetLeft(TrackIndex, 0);
            Canvas.SetLeft(TrackIndexPlay, 0);
            VolumeSlider.Value = volume;

            Log.Text = "KataTracks initializing\n";

            CombinedBluetoothController.Initialize();
            CombinedBluetoothController.FindPaired(leaderDeviceName,followDeviceName);

            
            foreach (KeyValuePair<string, BluetoothDeviceInfo> kvp in CombinedBluetoothController.pairedBluetoothDevices)
            {
                Log.Text += "Device: " + kvp.Key + " " + kvp.Value.DeviceAddress + "\n";
            }


            foreach (KeyValuePair<string, BluetoothClient> kvp in CombinedBluetoothController.pairedBluetoothConnections)
            {
                Log.Text += "Online: " + kvp.Key + " (" + CombinedBluetoothController.pairedBluetoothDevices[kvp.Key].DeviceAddress + ")\n";
                LeaderText.Text = "Online: " + kvp.Key + " (" + CombinedBluetoothController.pairedBluetoothDevices[kvp.Key].DeviceAddress + ")\n";
                FollowText.Text = "Online: " + kvp.Key + " (" + CombinedBluetoothController.pairedBluetoothDevices[kvp.Key].DeviceAddress + ")\n";
            }

            TrackView.Text = Fx.Get();

            Log.Text += "Timer created\n";
            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            dispatcherTimer.Start();
        }


        private void PlayTrack(int seconds)
        {
            if (playing)
                return;

            Log.Text += "Playing Track @" + seconds + " seconds\n";

            var audioFile = new AudioFileReader(filename);

            audioFile.Skip((int)(seconds));
            outputDevice.Init(audioFile);

            /*long time = timePlay + (long)timeValue;
            string timeStr = "@" + (time*100) + "\n";
            LeaderText.Text = timeStr;
            CombinedBluetoothController.SendMessage(leaderDeviceName, timeStr);*/

            string code = "@" + (timePick * 100) + "\r\n";
            CombinedBluetoothController.SendMessage(leaderDeviceName, code);
            CombinedBluetoothController.SendMessage(followDeviceName, code);


            //CombinedBluetoothController.SendMessage(followDeviceName, ")");
            outputDevice.Play();
            outputDevice.Volume = volume;
            literalTrackStartTime = DateTime.Now;
            playing = true;
        }

        private void StopTrack(bool resetLocation)
        {
            Log.Text += "Stopping track\n";

            outputDevice.Stop();
            //dispatcherTimer.Stop();
            playing = false;
            if (resetLocation)
            {
                Canvas.SetLeft(TrackIndexPlay, 0);
            }
            CombinedBluetoothController.SendMessage(leaderDeviceName, "(");
            CombinedBluetoothController.SendMessage(followDeviceName, "(");
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {            
            if (!playing) BluetoothStatus.Content = "Stopped";
            else BluetoothStatus.Content = "Playing";

            if (CombinedBluetoothController.IsOnline(leaderDeviceName))
                BluetoothStatus.Content += " Lead";
            if (CombinedBluetoothController.IsOnline(followDeviceName))
                BluetoothStatus.Content += " Follow";
            
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


            double timeValue = (double)(timeCurrentInSong.TotalMilliseconds)/100;
            Canvas.SetLeft(TrackIndexPlay, Math.Round(timeValue, 0));

            /*long time = timePlay + (long)timeValue;
            string timeStr = "@" + (time*100) + "\n";
            LeaderText.Text = timeStr;
            CombinedBluetoothController.SendMessage(leaderDeviceName, timeStr);*/

            //trackStartTime = DateTime.Now - new TimeSpan(0, 0, 0, 0, (int)timePick * 100);
            //CombinedBluetoothController.SendMessage("Follow", timeStr);

            CommandManager.InvalidateRequerySuggested();
        }

        private void Exit(object sender, RoutedEventArgs e)
        {
            Log.Text += "Exiting\n";

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
            ts = Math.Round(ts/10, 0);
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

                X = Math.Round(X/10,0)*10;
                Canvas.SetLeft(TrackIndex, X);

                TimeSpan ts = new TimeSpan(0, 0, 0, 0, (int)timePick*100);// DateTime.Now - trackStartTime;
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
    }
}
