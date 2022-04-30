﻿using System;
using System.Collections.Generic;
using NAudio.Wave;
using NAudio.CoreAudioApi;
using NAudio.Wave;
//using NAudioDemo.Utils;

namespace SoundLevels
{
    class VolumeMonitor
    {
        private static IWaveIn captureDevice;
        private static float trackMax = 0;

        //Between 0 and 1
        public static float GetVolume() { return trackMax;  }

        private static void OnDataAvailable(object sender, WaveInEventArgs args)
        {
            float max = 0;
            // interpret as 16 bit audio
            for (int index = 0; index < args.BytesRecorded; index += 2)
            {
                short sample = (short)((args.Buffer[index + 1] << 8) |
                                        args.Buffer[index + 0]);
                // to floating point
                var sample32 = sample / 32768f;
                // absolute value 
                if (sample32 < 0) sample32 = -sample32;
                // is this the max value?
                if (sample32 > max) max = sample32;
            }
            trackMax = max;
        }

        public static void EnumDevices()
        {
            var deviceEnum = new MMDeviceEnumerator();
            var devices = deviceEnum.EnumerateAudioEndPoints(DataFlow.Capture, DeviceState.Active); //.ToList();

            var renderDevices = deviceEnum.EnumerateAudioEndPoints(DataFlow.Render, DeviceState.Active);//.ToList();
            foreach (var rd in renderDevices)
                Console.WriteLine("Device: " + rd.DeviceFriendlyName + " = " + rd.AudioEndpointVolume.MasterVolumeLevel);
        }

        public static int GetInputDeviceNumber(string deviceName)
        {
            var deviceEnum = new MMDeviceEnumerator();
            var captureDevices = deviceEnum.EnumerateAudioEndPoints(DataFlow.Capture, DeviceState.Active); //.ToList();
            int deviceNumber = 0;
            foreach (var rd in captureDevices)
            {
                if (String.Compare(rd.DeviceFriendlyName.ToUpper(), deviceName.ToUpper()) == 0)
                    return deviceNumber;
                deviceNumber++;
            }
            return 0;
        }

        public static void Use(string deviceName)
        {
            string deviceSearchName = "Yeti Stereo Microphone";
            int deviceNumber = GetInputDeviceNumber(deviceSearchName);

            Console.WriteLine("Device number for " + deviceSearchName + " is " + deviceNumber);
            var newWaveIn = new WaveInEvent() { DeviceNumber = deviceNumber };

            newWaveIn.WaveFormat = new WaveFormat(11050, 2);
            newWaveIn.DataAvailable += OnDataAvailable;

            newWaveIn.StartRecording();
        }


    };

    class Program
    {
        static void Main(string[] args)
        {
            VolumeMonitor.Use("Yeti Stereo Microphone");

            while (true)
            {
                Console.WriteLine("Max = " + (int)(VolumeMonitor.GetVolume()*100));
            }
        }
    }
}