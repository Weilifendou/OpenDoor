using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Windows.Forms;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;

namespace BLELowVersion
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
            this.bleCore.MessAgeChanged += BleCore_MessAgeChanged;
            this.bleCore.DeviceWatcherChanged += BleCore_DeviceWatcherChanged;
            this.bleCore.GattDeviceServiceAdded += BleCore_GattDeviceServiceAdded;
            this.bleCore.CharacteristicAdded += BleCore_CharacteristicAdded;
            this.Init();
        }

        // 异步线程
        public static void RunAsync(Action action)
        {
            ((Action)(delegate ()
            {
                action.Invoke();
            })).BeginInvoke(null, null);
        }

        BleCore bleCore = new BleCore();
        /// <summary>
        /// 存储检测到的设备
        /// </summary>
        List<BluetoothLEDevice> DeviceList = new List<BluetoothLEDevice>();

        /// <summary>
        /// 当前蓝牙服务列表
        /// </summary>
        List<GattDeviceService> GattDeviceServices = new List<GattDeviceService>();

        /// <summary>
        /// 当前蓝牙服务特征列表
        /// </summary>
        List<GattCharacteristic> GattCharacteristics = new List<GattCharacteristic>();

        private void btnSearch_Click(object sender, EventArgs e)
        {
            if (this.btnSearch.Text == "搜索")
            {
                this.listboxMessage.Items.Clear();
                this.listboxBleDevice.Items.Clear();
                this.bleCore.StartBleDeviceWatcher();
                this.btnSearch.Text = "停止";
            }
            else
            {
                this.bleCore.StopBleDeviceWatcher();
                this.btnSearch.Text = "搜索";
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (this.listboxBleDevice.SelectedItem != null)
            {
                string DeviceName = this.listboxBleDevice.SelectedItem.ToString();
                Windows.Devices.Bluetooth.BluetoothLEDevice bluetoothLEDevice = this.DeviceList.Where(u => u.Name == DeviceName).FirstOrDefault();
                if (bluetoothLEDevice != null)
                {
                    bleCore.StartMatching(bluetoothLEDevice);
                    this.btnServer.Enabled = true;
                }
                else
                {
                    MessageBox.Show("没有发现此蓝牙，请重新搜索.");
                    this.btnServer.Enabled = false;
                }
            }
            else
            {
                MessageBox.Show("请选择连接的蓝牙.");
                this.btnServer.Enabled = false;
            }
        }

        private void btnServer_Click(object sender, EventArgs e)
        {
            this.cmbServer.Items.Clear();
            this.bleCore.FindService();
        }

        private void btnFeatures_Click(object sender, EventArgs e)
        {
            this.cmbFeatures.Items.Clear();
            if (this.cmbServer.SelectedItem != null)
            {
                var item = this.GattDeviceServices.Where(u => u.Uuid == new Guid(this.cmbServer.SelectedItem.ToString())).FirstOrDefault();
                this.bleCore.FindCharacteristic(item);
            }
            else
            {
                MessageBox.Show("选择蓝牙服务.");
            }
        }

        private void btnOpteron_Click(object sender, EventArgs e)
        {
            if (this.cmbFeatures.SelectedItem != null)
            {
                var item = this.GattCharacteristics.Where(u => u.Uuid == new Guid(this.cmbFeatures.SelectedItem.ToString())).FirstOrDefault();
                this.bleCore.SetOpteron(item);
                if (item.CharacteristicProperties == (Windows.Devices.Bluetooth.GenericAttributeProfile.GattCharacteristicProperties.Notify | Windows.Devices.Bluetooth.GenericAttributeProfile.GattCharacteristicProperties.Read | Windows.Devices.Bluetooth.GenericAttributeProfile.GattCharacteristicProperties.Write))
                {
                    this.btnReader.Enabled = true;
                    this.btnSend.Enabled = true;
                }
            }
            else
            {
                MessageBox.Show("选择蓝牙服务.");
            }
        }

        private void btnReader_Click(object sender, EventArgs e)
        {

        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            byte[] dataBytes = new byte[6];

            dataBytes[0] = 0x23;
            dataBytes[1] = 0x00;
            dataBytes[2] = 0x02;
            dataBytes[3] = 0x01;
            dataBytes[4] = (byte)(dataBytes[1] + dataBytes[2] + dataBytes[3]);
            dataBytes[5] = 0x2A;

            this.bleCore.Write(dataBytes);
        }

        /// <summary>
        /// 提示消息
        /// </summary>
        private void BleCore_MessAgeChanged(MsgType type, string message, byte[] data)
        {
            RunAsync(() =>
            {
                this.listboxMessage.Items.Add(message);
            });
        }

        /// <summary>
        /// 搜索蓝牙设备列表
        /// </summary>
        private void BleCore_DeviceWatcherChanged(MsgType type, Windows.Devices.Bluetooth.BluetoothLEDevice bluetoothLEDevice)
        {
            RunAsync(() =>
            {
                this.listboxBleDevice.Items.Add(bluetoothLEDevice.Name);
                this.DeviceList.Add(bluetoothLEDevice);
                this.btnConnect.Enabled = true;
            });
        }

        /// <summary>
        /// 获取蓝牙服务列表
        /// </summary>
        private void BleCore_GattDeviceServiceAdded(Windows.Devices.Bluetooth.GenericAttributeProfile.GattDeviceService gattDeviceService)
        {
            RunAsync(() =>
            {
                this.cmbServer.Items.Add(gattDeviceService.Uuid.ToString());
                this.GattDeviceServices.Add(gattDeviceService);
                this.btnFeatures.Enabled = true;
            });
        }

        /// <summary>
        /// 获取特征列表
        /// </summary>
        private void BleCore_CharacteristicAdded(Windows.Devices.Bluetooth.GenericAttributeProfile.GattCharacteristic gattCharacteristic)
        {
            RunAsync(() =>
            {
                this.cmbFeatures.Items.Add(gattCharacteristic.Uuid);
                this.GattCharacteristics.Add(gattCharacteristic);
                this.btnOpteron.Enabled = true;
            });
        }

        private void Init()
        {
            this.btnConnect.Enabled = false;
            this.btnServer.Enabled = false;
            this.btnFeatures.Enabled = false;
            this.btnOpteron.Enabled = false;
            this.btnReader.Enabled = false;
            this.btnSend.Enabled = false;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.bleCore.Dispose();
        }
    }
}