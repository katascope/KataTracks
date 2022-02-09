﻿using System;
using System.Collections.Generic;
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
        static DateTime trackStartTime;
        float volume = 0.25f;
        static long timeMs = 0;
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


            CombinedBluetoothController.Initialize();
            CombinedBluetoothController.FindPaired(leaderDeviceName,"");

            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            dispatcherTimer.Start();
        }

        private void PlayTrack(int seconds)
        {
            var audioFile = new AudioFileReader(filename);

            audioFile.Skip((int)(seconds));
            outputDevice.Init(audioFile);
            CombinedBluetoothController.SendMessage(leaderDeviceName, ")");
            //CombinedBluetoothController.SendMessage(followDeviceName, ")");
            outputDevice.Play();
            outputDevice.Volume = volume;
            trackStartTime = DateTime.Now;
            playing = true;
        }

        private void StopTrack(bool resetLocation)
        {
            outputDevice.Stop();
            //dispatcherTimer.Stop();
            playing = false;
            if (resetLocation)
            {
                Canvas.SetLeft(TrackIndexPlay, 0);
            }
            CombinedBluetoothController.SendMessage(leaderDeviceName, "(");
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
            TimeSpan timeElapsedSincePlay = DateTime.Now - trackStartTime + new TimeSpan(0,0,0,0,(int)timePick*100);
            TrackTime.Content = ""
                + timeElapsedSincePlay.Minutes + ":"
                + timeElapsedSincePlay.Seconds + ":"
                + timeElapsedSincePlay.Milliseconds / 100;
            double timeValue = (double)(timeElapsedSincePlay.TotalMilliseconds / 100);

            Canvas.SetLeft(TrackIndexPlay, timeMs+timeValue);

            long time = timeMs + (long)timeValue;
            string timeStr = "@" + time + "\n";
            //combinedBluetoothController.SendMessage(leaderDeviceName, timeStr);
            //CombinedBluetoothController.SendMessage("Follow", timeStr);

            CommandManager.InvalidateRequerySuggested();
        }

        private void Exit(object sender, RoutedEventArgs e)
        {
            CombinedBluetoothController.Close();
            System.Windows.Application.Current.Shutdown();
        }

        private void PlayButton_Click(object sender, RoutedEventArgs e)
        {
            int ts = (int)(timePick /10);
            PlayTrack(ts);
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
                Canvas.SetLeft(TrackIndex, X);

                TimeSpan ts = new TimeSpan(0, 0, 0, 0, (int)timePick*100);// DateTime.Now - trackStartTime;
                TrackTimeOffset.Content = ""
                    + ts.Minutes + ":"
                    + ts.Seconds + ":"
                    + ts.Milliseconds / 100;

            }
        }

        private void VolumeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            volume = (float)e.NewValue;            
            outputDevice.Volume = volume;
        }
    }
}
