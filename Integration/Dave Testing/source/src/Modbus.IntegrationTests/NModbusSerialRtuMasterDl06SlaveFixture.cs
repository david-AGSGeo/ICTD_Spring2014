using Modbus.Device;
using MbUnit.Framework;
using System;

namespace Modbus.IntegrationTests
{
	[TestFixture]
	public class NModbusSerialRtuMasterDl06SlaveFixture : ModbusSerialMasterFixture
	{
		[TestFixtureSetUp]
		public override void Init()
		{
			base.Init();

			MasterSerialPort = CreateAndOpenSerialPort("COM4");
			Master = ModbusSerialMaster.CreateRtu(MasterSerialPort);
		}

		/// <summary>
		/// Not supported by the DL06
		/// </summary>
		public override void ReadWriteMultipleRegisters()
		{
		}

		/// <summary>
		/// Not supported by the DL06
		/// </summary>
		public override void ReturnQueryData()
		{
		}		

		[Test]
		public override void ReadCoils()
		{
			base.ReadCoils();
		}
	}
}
