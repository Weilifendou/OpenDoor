using System;
using System.Collections.Generic;
using System.Threading;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Foundation;
using Windows.Security.Cryptography;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Template
{
    public class BleCore
    {

        private BluetoothLEAdvertisementWatcher deviceWatcher;
        private BluetoothLEDevice currentDevice;
        private bool asyncLock = false;
        public readonly List<BluetoothLEDevice> deviceList = new List<BluetoothLEDevice>();
        public delegate void DeviceWatcherChangeEvent(BluetoothLEDevice bluetoothLEDevice);
        public event DeviceWatcherChangeEvent DeviceWatcherChanged;
        public delegate void DeviceStatusChangeEvent(bool status);
        public event DeviceStatusChangeEvent DeviceStatusChanged;
        public delegate void DeviceReceiveDataEvent(byte[] data);
        public event DeviceReceiveDataEvent DeviceReceiveData;
        public GattCharacteristic WriteCharacteristic;
        public GattCharacteristic NotifyCharacteristic;
        public bool status = false;

        public void StartBleDeviceWatcher()
        {
            deviceWatcher = new BluetoothLEAdvertisementWatcher
            {
                ScanningMode = BluetoothLEScanningMode.Active
            };
            deviceWatcher.SignalStrengthFilter.InRangeThresholdInDBm = -80;
            deviceWatcher.SignalStrengthFilter.OutOfRangeThresholdInDBm = -90;
            deviceWatcher.SignalStrengthFilter.OutOfRangeTimeout = TimeSpan.FromMilliseconds(5000);
            deviceWatcher.SignalStrengthFilter.SamplingInterval = TimeSpan.FromMilliseconds(2000);

            deviceWatcher.Received += DeviceWatcher_Received;
            deviceWatcher.Stopped += DeviceWatcher_Stopped;
            try
            {
                deviceWatcher.Start();
            }
            catch { }
        }
        public void StopBleDeviceWathcer()
        {
            deviceWatcher?.Stop();
        }

        private void DeviceWatcher_Stopped(BluetoothLEAdvertisementWatcher sender, BluetoothLEAdvertisementWatcherStoppedEventArgs args)
        {
        }

        private void DeviceWatcher_Received(BluetoothLEAdvertisementWatcher sender, BluetoothLEAdvertisementReceivedEventArgs args)
        {
            BluetoothLEDevice.FromBluetoothAddressAsync(args.BluetoothAddress).Completed = (asyncInfo, asyncStatus) =>
            {
                if (asyncStatus == AsyncStatus.Completed)
                {
                    if (asyncInfo.GetResults() != null)
                    {
                        BluetoothLEDevice currentDevice = asyncInfo.GetResults();

                        bool contain = false;
                        foreach (BluetoothLEDevice device in deviceList)//过滤重复的设备
                        {
                            if (device.DeviceId == currentDevice.DeviceId)
                            {
                                contain = true;
                            }
                        }
                        if (!contain)
                        {
                            DeviceWatcherChanged(currentDevice);
                            deviceList.Add(currentDevice);
                        }
                    }
                }
            };
        }
        public void FindService(BluetoothLEDevice device)
        {
            currentDevice = device;
            if (currentDevice != null)
            {
                currentDevice.ConnectionStatusChanged += CurrentDevice_ConnectionStatusChanged;
                currentDevice.GetGattServicesAsync().Completed = (asyncInfo, asyncStatus) =>
                {
                    status = true;
                    DeviceStatusChanged(status);
                    if (asyncStatus == AsyncStatus.Completed)
                    {
                        var services = asyncInfo.GetResults().Services;
                        foreach (var service in services)
                        {
                            FindCharacteristic(service);
                        }
                    }
                };

            }
        }
        private void CurrentDevice_ConnectionStatusChanged(BluetoothLEDevice sender, object args)
        {
            if (sender.ConnectionStatus == BluetoothConnectionStatus.Disconnected)
            {
                if (!asyncLock)
                {
                    asyncLock = true;
                }
            }
        }
        private void FindCharacteristic(GattDeviceService gattDeviceService)
        {
            gattDeviceService.GetCharacteristicsAsync().Completed = (asyncInfo, asyncStatus) =>
            {
                if (asyncStatus == AsyncStatus.Completed)
                {
                    var services = asyncInfo.GetResults().Characteristics;
                    foreach (var c in services)
                    {
                        var properties = c.CharacteristicProperties;
                        if (properties.HasFlag(GattCharacteristicProperties.Read))
                        {
                            NotifyCharacteristic = c;
                            NotifyCharacteristic.ProtectionLevel = GattProtectionLevel.Plain;
                            NotifyCharacteristic.ValueChanged += Characteristic_ValueChanged;
                            EnableNotifications();
                        }
                        if (properties.HasFlag(GattCharacteristicProperties.Write))
                        {
                            WriteCharacteristic = c;
                        }

                    }

                }
            };
        }
        private void EnableNotifications()
        {
            NotifyCharacteristic.WriteClientCharacteristicConfigurationDescriptorAsync(
            GattClientCharacteristicConfigurationDescriptorValue.Notify).Completed = (asyncInfo, asyncStatus) =>
            {
                if (asyncStatus == AsyncStatus.Completed)
                {
                    GattCommunicationStatus status = asyncInfo.GetResults();
                    if (status == GattCommunicationStatus.Unreachable)
                    {
                        if (!asyncLock)
                        {
                            EnableNotifications();
                        }
                    }
                    asyncLock = false;
                }
            };
        }
        private void Characteristic_ValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args)
        {
            CryptographicBuffer.CopyToByteArray(args.CharacteristicValue, out byte[] data);
            DeviceReceiveData(data);
        }

        public void Write(byte[] data)
        {
            if (WriteCharacteristic != null)
            {
                WriteCharacteristic.WriteValueAsync(CryptographicBuffer.CreateFromByteArray(data),
                GattWriteOption.WriteWithResponse).Completed = (asyncInfo, asyncStatus) =>
                {
                    if (asyncStatus == AsyncStatus.Completed)
                    {
                        asyncInfo.GetResults();
                    }
                };

            }

        }
        public void DeviceDispose()
        {
            status = false;
            DeviceStatusChanged(status);
            WriteCharacteristic = null;
            NotifyCharacteristic = null;
        }
    }
}