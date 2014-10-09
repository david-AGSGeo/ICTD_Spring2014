using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using ABB.Robotics;
using ABB.Robotics.Controllers;
using ABB.Robotics.Controllers.Discovery;
using ABB.Robotics.Controllers.RapidDomain;

namespace Integration_Control
{
    public partial class Form1 : Form
    {
        private NetworkScanner networkScanner = null;
        private Controller ctrl = null;
        private Task[] tasks = null;
        private NetworkWatcher NetworkWatcher = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void Initialise_Controller(object sender, EventArgs e)
        {
            this.networkScanner = new NetworkScanner();     //scan network for robots and add them to the listview
            this.networkScanner.Scan();
            ControllerInfoCollection controllers = networkScanner.Controllers;
            foreach (ControllerInfo controller in controllers) 
            {
                ListViewItem item = new ListViewItem(controller.SystemName);
                item.SubItems.Add(controller.IPAddress.ToString());
                item.SubItems.Add(controller.Version.ToString());
                item.Tag = controller;
                this.Robot_Controllers.Items.Add(item);

            }

            this.NetworkWatcher = new NetworkWatcher(networkScanner.Controllers);
            this.NetworkWatcher.Found += NetworkWatcher_Found;
            this.NetworkWatcher.Lost += NetworkWatcher_Lost;
            this.NetworkWatcher.EnableRaisingEvents = true;
            Update();
        }

        void NetworkWatcher_Lost(object sender, NetworkWatcherEventArgs e)
        {
            throw new NotImplementedException();
        }

        void NetworkWatcher_Found(object sender, NetworkWatcherEventArgs e)
        {
            this.Invoke(new EventHandler<NetworkWatcherEventArgs>(AddControllerToListView), new Object[] { this, e});
        }

        private void AddControllerToListView(object sender, NetworkWatcherEventArgs e)
        {
            ControllerInfo controller = e.Controller;
            ListViewItem item = new ListViewItem(controller.SystemName);
            item.SubItems.Add(controller.IPAddress.ToString());
            item.SubItems.Add(controller.Version.ToString());
            item.Tag = controller;
            this.Robot_Controllers.Items.Add(item);
 
        }



        private void Robot_Controllers_DoubleClick(object sender, EventArgs e)
        {
            ListViewItem itemView = Robot_Controllers.SelectedItems[0];
            if (itemView != null)
            {
                if (ctrl != null)
                {
                    ctrl.Logoff();
                    ctrl.Dispose();
                }
                ControllerInfo controllerInfo = (ControllerInfo)itemView.Tag;
                ctrl = ControllerFactory.CreateFrom(controllerInfo);
                ctrl.Logon(UserInfo.DefaultUser);
                ListViewItem item = new ListViewItem(ctrl.RobotWare.ToString() + " " + ctrl.State.ToString() 
                    + " " + ctrl.OperatingMode.ToString());
                this.Robot_Data.Items.Add(item);

            }
        }

        private void Start_Click(object sender, EventArgs e)
        {
            try
            {
                if (ctrl.OperatingMode == ControllerOperatingMode.Auto)
                {
                    tasks = ctrl.Rapid.GetTasks();
                    using (Mastership m = Mastership.Request(ctrl.Rapid))
                    {
                        tasks[0].Start();
                    }
                }
                else
                {
                    MessageBox.Show("Automatic mode is required to start execution from a remote client");
                }
            }
            catch (System.InvalidOperationException ex)
            {
                MessageBox.Show("Mastership is held by another client " + ex.Message);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Unexpected Exception:  " + ex.Message);
            }
        }


    }
}
