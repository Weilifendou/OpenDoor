using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Foundation;
using Windows.Networking;
using Windows.Networking.Proximity;
using Windows.Networking.Sockets;
using Windows.Security.Cryptography;
using Windows.Storage.Streams;

namespace TestBle
{
    public class BleCore
    {
        private bool asyncLock = false;

        /// <summary>
        /// 搜索蓝牙设备对象
        /// </summary>
        private DeviceWatcher deviceWatcher;

        /// <summary>
        /// 当前连接的服务
        /// </summary>
        public GattDeviceService CurrentService { get; set; }

        /// <summary>
        /// 当前连接的蓝牙设备
        /// </summary>
        public BluetoothLEDevice CurrentDevice { get; set; }

        /// <summary>
        /// 写特征对象
        /// </summary>
        public GattCharacteristic CurrentWriteCharacteristic { get; set; }

        /// <summary>
        /// 通知特征对象
        /// </summary>
        public GattCharacteristic CurrentNotifyCharacteristic { get; set; }

        /// <summary>
        /// 特性通知类型通知启用
        /// </summary>
        private const GattClientCharacteristicConfigurationDescriptorValue CHARACTERISTIC_NOTIFICATION_TYPE = GattClientCharacteristicConfigurationDescriptorValue.Notify;

        /// <summary>
        /// 存储检测到的设备
        /// </summary>
        private List<BluetoothLEDevice> DeviceList = new List<BluetoothLEDevice>();

        /// <summary>
        /// 定义搜索蓝牙设备委托
        /// </summary>
        public delegate void DeviceWatcherChangedEvent(MsgType type, BluetoothLEDevice bluetoothLEDevice);

        /// <summary>
        /// 搜索蓝牙事件
        /// </summary>
        public event DeviceWatcherChangedEvent DeviceWatcherChanged;

        /// <summary>
        /// 获取服务委托
        /// </summary>
        public delegate void GattDeviceServiceAddedEvent(GattDeviceService gattDeviceService);

        /// <summary>
        /// 获取服务事件
        /// </summary>
        public event GattDeviceServiceAddedEvent GattDeviceServiceAdded;

        /// <summary>
        /// 获取特征委托
        /// </summary>
        public delegate void CharacteristicAddedEvent(GattCharacteristic gattCharacteristic);

        /// <summary>
        /// 获取特征事件
        /// </summary>
        public event CharacteristicAddedEvent CharacteristicAdded;

        /// <summary>
        /// 提示信息委托
        /// </summary>
        public delegate void MessAgeChangedEvent(MsgType type, string message, byte[] data = null);

        /// <summary>
        /// 提示信息事件
        /// </summary>
        public event MessAgeChangedEvent MessAgeChanged;

        /// <summary>
        /// 当前连接的蓝牙Mac
        /// </summary>
        private string CurrentDeviceMAC { get; set; }

        public BleCore()
        {
            Windows.Devices.Bluetooth.BluetoothCacheMode
        }

        /// <summary>
        /// 搜索蓝牙设备
        /// </summary>
        public void StartBleDeviceWatcher()
        {
            string[] requestedProperties = { "System.Devices.Aep.DeviceAddress", "System.Devices.Aep.IsConnected", "System.Devices.Aep.Bluetooth.Le.IsConnectable" };
            string aqsAllBluetoothLEDevices = "(System.Devices.Aep.ProtocolId:=\"{bb7bb05e-5972-42b5-94fc-76eaa7084d49}\")";

            deviceWatcher =
                    DeviceInformation.CreateWatcher(
                        aqsAllBluetoothLEDevices,
                        requestedProperties,
                        DeviceInformationKind.AssociationEndpoint);

            // Register event handlers before starting the watcher.
            deviceWatcher.Added += this.DeviceWatcher_Added;
            deviceWatcher.Stopped += this.DeviceWatcher_Stopped;
            deviceWatcher.Start();
            string msg = "自动发现设备中..";

            MessAgeChanged(MsgType.NotifyTxt, msg);
        }

        /// <summary>
        /// 停止搜索蓝牙
        /// </summary>
        public void StopBleDeviceWatcher()
        {
            deviceWatcher.Stop();
        }

        /// <summary>
        /// 获取发现的蓝牙设备
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation args)
        {
            MessAgeChanged(MsgType.NotifyTxt, "发现设备:" + args.Id);
            Matching(args.Id);
        }

        /// <summary>
        /// 停止搜索蓝牙设备
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void DeviceWatcher_Stopped(DeviceWatcher sender, object args)
        {
            string msg = "自动发现设备停止";
            MessAgeChanged(MsgType.NotifyTxt, msg);
        }

        /// <summary>
        /// 匹配
        /// </summary>
        /// <param name="Device"></param>
        public void StartMatching(BluetoothLEDevice Device)
        {
            CurrentDevice = Device;
        }

        /// <summary>
        /// 获取蓝牙服务
        /// </summary>
        public async void FindService()
        {
            var GattServices = CurrentDevice.GattServices;
            foreach (GattDeviceService ser in GattServices)
            {
                GattDeviceServiceAdded(ser);
            }
        }

        /// <summary>
        /// 获取特性
        /// </summary>
        public async void FindCharacteristic(GattDeviceService gattDeviceService)
        {
            CurrentService = gattDeviceService;
            foreach (var c in gattDeviceService.GetAllCharacteristics())
            {
                CharacteristicAdded(c);
            }
        }

        /// <summary>
        /// 获取操作
        /// </summary>
        /// <returns></returns>
        public async Task SetOpteron(GattCharacteristic gattCharacteristic)
        {
            if (gattCharacteristic.CharacteristicProperties == GattCharacteristicProperties.Write)
            {
                CurrentWriteCharacteristic = gattCharacteristic;
            }
            if (gattCharacteristic.CharacteristicProperties == GattCharacteristicProperties.Notify)
            {
                CurrentNotifyCharacteristic = gattCharacteristic;
            }
            if ((uint)gattCharacteristic.CharacteristicProperties == 26)
            { }

            if (gattCharacteristic.CharacteristicProperties == (GattCharacteristicProperties.Notify | GattCharacteristicProperties.Read | GattCharacteristicProperties.Write))
            {
                CurrentWriteCharacteristic = gattCharacteristic;

                CurrentNotifyCharacteristic = gattCharacteristic;
                CurrentNotifyCharacteristic.ProtectionLevel = GattProtectionLevel.Plain;
                CurrentNotifyCharacteristic.ValueChanged += Characteristic_ValueChanged;
                await EnableNotifications(CurrentNotifyCharacteristic);
            }

            Connect();
        }

        /// <summary>
        /// 连接蓝牙
        /// </summary>
        /// <returns></returns>
        private async Task Connect()
        {
            byte[] _Bytes1 = BitConverter.GetBytes(CurrentDevice.BluetoothAddress);
            Array.Reverse(_Bytes1);
            CurrentDeviceMAC = BitConverter.ToString(_Bytes1, 2, 6).Replace('-', ':').ToLower();

            string msg = "正在连接设备<" + CurrentDeviceMAC + ">..";
            MessAgeChanged(MsgType.NotifyTxt, msg);
            CurrentDevice.ConnectionStatusChanged += this.CurrentDevice_ConnectionStatusChanged;
        }

        /// <summary>
        /// 搜索到的蓝牙设备
        /// </summary>
        /// <returns></returns>
        private async Task Matching(string Id)
        {
            try
            {
                BluetoothLEDevice.FromIdAsync(Id).Completed = async (asyncInfo, asyncStatus) =>
                {
                    if (asyncStatus == AsyncStatus.Completed)
                    {
                        BluetoothLEDevice bleDevice = asyncInfo.GetResults();
                        DeviceList.Add(bleDevice);
                        DeviceWatcherChanged(MsgType.BleDevice, bleDevice);
                    }
                };
            }
            catch (Exception e)
            {
                string msg = "没有发现设备" + e.ToString();
                MessAgeChanged(MsgType.NotifyTxt, msg);
                StartBleDeviceWatcher();
            }
        }

        /// <summary>
        /// 主动断开连接
        /// </summary>
        /// <returns></returns>
        public void Dispose()
        {

            CurrentDeviceMAC = null;
            CurrentService?.Dispose();
            CurrentDevice?.Dispose();
            CurrentDevice = null;
            CurrentService = null;
            CurrentWriteCharacteristic = null;
            CurrentNotifyCharacteristic = null;
            MessAgeChanged(MsgType.NotifyTxt, "主动断开连接");
        }

        private void CurrentDevice_ConnectionStatusChanged(BluetoothLEDevice sender, object args)
        {
            if (sender.ConnectionStatus == BluetoothConnectionStatus.Disconnected && CurrentDeviceMAC != null)
            {
                string msg = "设备已断开,自动重连";
                MessAgeChanged(MsgType.NotifyTxt, msg);
                if (!asyncLock)
                {
                    asyncLock = true;
                    CurrentDevice.Dispose();
                    CurrentDevice = null;
                    CurrentService = null;
                    CurrentWriteCharacteristic = null;
                    CurrentNotifyCharacteristic = null;
                    SelectDeviceFromIdAsync(CurrentDeviceMAC);
                }
            }
            else
            {
                string msg = "设备已连接";
                MessAgeChanged(MsgType.NotifyTxt, msg);
            }
        }

        /// <summary>
        /// 按MAC地址直接组装设备ID查找设备
        /// </summary>
        public async Task SelectDeviceFromIdAsync(string MAC)
        {
            CurrentDeviceMAC = MAC;
            CurrentDevice = null;
            BluetoothAdapter.GetDefaultAsync().Completed = async (asyncInfo, asyncStatus) =>
            {
                if (asyncStatus == AsyncStatus.Completed)
                {
                    BluetoothAdapter mBluetoothAdapter = asyncInfo.GetResults();
                    byte[] _Bytes1 = BitConverter.GetBytes(mBluetoothAdapter.BluetoothAddress);//ulong转换为byte数组
                    Array.Reverse(_Bytes1);
                    string macAddress = BitConverter.ToString(_Bytes1, 2, 6).Replace('-', ':').ToLower();
                    string Id = "BluetoothLE#BluetoothLE" + macAddress + "-" + MAC;
                    await Matching(Id);
                }
            };
        }

        /// <summary>
        /// 设置特征对象为接收通知对象
        /// </summary>
        /// <param name="characteristic"></param>
        /// <returns></returns>
        public async Task EnableNotifications(GattCharacteristic characteristic)
        {
            string msg = "收通知对象=" + CurrentDevice.ConnectionStatus;
            MessAgeChanged(MsgType.NotifyTxt, msg);

            characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(CHARACTERISTIC_NOTIFICATION_TYPE).Completed = async (asyncInfo, asyncStatus) =>
            {
                if (asyncStatus == AsyncStatus.Completed)
                {
                    GattCommunicationStatus status = asyncInfo.GetResults();
                    if (status == GattCommunicationStatus.Unreachable)
                    {
                        msg = "设备不可用";
                        MessAgeChanged(MsgType.NotifyTxt, msg);
                        if (CurrentNotifyCharacteristic != null && !asyncLock)
                        {
                            await EnableNotifications(CurrentNotifyCharacteristic);
                        }
                    }
                    asyncLock = false;
                    msg = "设备连接状态" + status;
                    MessAgeChanged(MsgType.NotifyTxt, msg);
                }
            };
        }

        /// <summary>
        /// 接受到蓝牙数据
        /// </summary>
        private void Characteristic_ValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args)
        {
            byte[] data;
            CryptographicBuffer.CopyToByteArray(args.CharacteristicValue, out data);
            string str = BitConverter.ToString(data);
            MessAgeChanged(MsgType.BleData, str, data);
        }

        /// <summary>
        /// 发送数据接口
        /// </summary>
        /// <returns></returns>
        public async Task Write(byte[] data)
        {
            if (CurrentWriteCharacteristic != null)
            {
                CurrentWriteCharacteristic.WriteValueAsync(CryptographicBuffer.CreateFromByteArray(data), GattWriteOption.WriteWithResponse);
                string str = "发送数据：" + BitConverter.ToString(data);
                MessAgeChanged(MsgType.BleData, str, data);
            }

        }
    }
}