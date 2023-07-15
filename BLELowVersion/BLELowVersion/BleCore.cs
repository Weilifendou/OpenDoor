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

namespace BLELowVersion
{
    public enum MsgType
    {
        NotifyTxt,
        BleData,
        BleDevice

    }
    public class BleCore
    {
        private Boolean asyncLock = false;

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

        }

        /// <summary>
        /// 搜索蓝牙设备
        /// </summary>
        public void StartBleDeviceWatcher()
        {
            string[] requestedProperties = { "System.Devices.Aep.DeviceAddress", "System.Devices.Aep.IsConnected", "System.Devices.Aep.Bluetooth.Le.IsConnectable" };
            string aqsAllBluetoothLEDevices = "(System.Devices.Aep.ProtocolId:=\"{bb7bb05e-5972-42b5-94fc-76eaa7084d49}\")";

            this.deviceWatcher =
                    DeviceInformation.CreateWatcher(
                        aqsAllBluetoothLEDevices,
                        requestedProperties,
                        DeviceInformationKind.AssociationEndpoint);

            // Register event handlers before starting the watcher.
            this.deviceWatcher.Added += this.DeviceWatcher_Added;
            this.deviceWatcher.Stopped += this.DeviceWatcher_Stopped;
            this.deviceWatcher.Start();
            string msg = "自动发现设备中..";

            this.MessAgeChanged(MsgType.NotifyTxt, msg);
        }

        /// <summary>
        /// 停止搜索蓝牙
        /// </summary>
        public void StopBleDeviceWatcher()
        {
            this.deviceWatcher.Stop();
        }

        /// <summary>
        /// 获取发现的蓝牙设备
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation args)
        {
            this.MessAgeChanged(MsgType.NotifyTxt, "发现设备:" + args.Id);
            this.Matching(args.Id);
        }

        /// <summary>
        /// 停止搜索蓝牙设备
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        private void DeviceWatcher_Stopped(DeviceWatcher sender, object args)
        {
            string msg = "自动发现设备停止";
            this.MessAgeChanged(MsgType.NotifyTxt, msg);
        }

        /// <summary>
        /// 匹配
        /// </summary>
        /// <param name="Device"></param>
        public void StartMatching(BluetoothLEDevice Device)
        {
            this.CurrentDevice = Device;
        }

        /// <summary>
        /// 获取蓝牙服务
        /// </summary>
        public async void FindService()
        {
            var GattServices = this.CurrentDevice.GattServices;
            foreach (GattDeviceService ser in GattServices)
            {
                this.GattDeviceServiceAdded(ser);
            }
        }

        /// <summary>
        /// 获取特性
        /// </summary>
        public async void FindCharacteristic(GattDeviceService gattDeviceService)
        {
            this.CurrentService = gattDeviceService;
            foreach (var c in gattDeviceService.GetAllCharacteristics())
            {
                this.CharacteristicAdded(c);
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
                this.CurrentWriteCharacteristic = gattCharacteristic;
            }
            if (gattCharacteristic.CharacteristicProperties == GattCharacteristicProperties.Notify)
            {
                this.CurrentNotifyCharacteristic = gattCharacteristic;
            }
            if ((uint)gattCharacteristic.CharacteristicProperties == 26)
            { }

            if (gattCharacteristic.CharacteristicProperties == (GattCharacteristicProperties.Notify | GattCharacteristicProperties.Read | GattCharacteristicProperties.Write))
            {
                this.CurrentWriteCharacteristic = gattCharacteristic;

                this.CurrentNotifyCharacteristic = gattCharacteristic;
                this.CurrentNotifyCharacteristic.ProtectionLevel = GattProtectionLevel.Plain;
                this.CurrentNotifyCharacteristic.ValueChanged += Characteristic_ValueChanged;
                await this.EnableNotifications(CurrentNotifyCharacteristic);
            }

            this.Connect();
        }

        /// <summary>
        /// 连接蓝牙
        /// </summary>
        /// <returns></returns>
        private async Task Connect()
        {
            byte[] _Bytes1 = BitConverter.GetBytes(this.CurrentDevice.BluetoothAddress);
            Array.Reverse(_Bytes1);
            this.CurrentDeviceMAC = BitConverter.ToString(_Bytes1, 2, 6).Replace('-', ':').ToLower();

            string msg = "正在连接设备<" + this.CurrentDeviceMAC + ">..";
            this.MessAgeChanged(MsgType.NotifyTxt, msg);
            this.CurrentDevice.ConnectionStatusChanged += this.CurrentDevice_ConnectionStatusChanged;
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
                        this.DeviceList.Add(bleDevice);
                        this.DeviceWatcherChanged(MsgType.BleDevice, bleDevice);
                    }
                };
            }
            catch (Exception e)
            {
                string msg = "没有发现设备" + e.ToString();
                this.MessAgeChanged(MsgType.NotifyTxt, msg);
                this.StartBleDeviceWatcher();
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
                    this.CurrentDevice.Dispose();
                    this.CurrentDevice = null;
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
            this.MessAgeChanged(MsgType.NotifyTxt, msg);

            characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(CHARACTERISTIC_NOTIFICATION_TYPE).Completed = async (asyncInfo, asyncStatus) =>
            {
                if (asyncStatus == AsyncStatus.Completed)
                {
                    GattCommunicationStatus status = asyncInfo.GetResults();
                    if (status == GattCommunicationStatus.Unreachable)
                    {
                        msg = "设备不可用";
                        this.MessAgeChanged(MsgType.NotifyTxt, msg);
                        if (CurrentNotifyCharacteristic != null && !asyncLock)
                        {
                            await this.EnableNotifications(CurrentNotifyCharacteristic);
                        }
                    }
                    asyncLock = false;
                    msg = "设备连接状态" + status;
                    this.MessAgeChanged(MsgType.NotifyTxt, msg);
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
            this.MessAgeChanged(MsgType.BleData, str, data);
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
                this.MessAgeChanged(MsgType.BleData, str, data);
            }

        }
    }
}
