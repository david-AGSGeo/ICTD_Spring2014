using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using log4net;
using Modbus.Message;
using Modbus.Utility;
using Unme.Common;

namespace Modbus.IO
{
	/// <summary>	
	/// Refined Abstraction - http://en.wikipedia.org/wiki/Bridge_Pattern
	/// </summary>
	internal class ModbusRtuTransport : ModbusSerialTransport
	{
		public const int RequestFrameStartLength = 7;
		public const int ResponseFrameStartLength = 4;

		private static readonly ILog _logger = LogManager.GetLogger(typeof(ModbusRtuTransport));

		internal ModbusRtuTransport(IStreamResource streamResource)
			: base(streamResource)
		{
			Debug.Assert(streamResource != null, "Argument streamResource cannot be null.");
		}

		public static int RequestBytesToRead(byte[] frameStart)
		{
			byte functionCode = frameStart[1];
			int numBytes;

			switch (functionCode)
			{
				case Modbus.ReadCoils:
				case Modbus.ReadInputs:
				case Modbus.ReadHoldingRegisters:
				case Modbus.ReadInputRegisters:
				case Modbus.WriteSingleCoil:
				case Modbus.WriteSingleRegister:
				case Modbus.Diagnostics:
					numBytes = 1;
					break;
				case Modbus.WriteMultipleCoils:
				case Modbus.WriteMultipleRegisters:
					byte byteCount = frameStart[6];
					numBytes = byteCount + 2;
					break;
				default:
					string errorMessage = String.Format(CultureInfo.InvariantCulture, "Function code {0} not supported.", functionCode);
					_logger.Error(errorMessage);
					throw new NotImplementedException(errorMessage);
			}

			return numBytes;
		}

		public static int ResponseBytesToRead(byte[] frameStart)
		{
			byte functionCode = frameStart[1];

			// exception response
			if (functionCode > Modbus.ExceptionOffset)
				return 1;

			int numBytes;
			switch (functionCode)
			{
				case Modbus.ReadCoils:
				case Modbus.ReadInputs:
				case Modbus.ReadHoldingRegisters:
				case Modbus.ReadInputRegisters:
					numBytes = frameStart[2] + 1;
					break;
				case Modbus.WriteSingleCoil:
				case Modbus.WriteSingleRegister:
				case Modbus.WriteMultipleCoils:
				case Modbus.WriteMultipleRegisters:
				case Modbus.Diagnostics:
					numBytes = 4;
					break;
				default:
					string errorMessage = String.Format(CultureInfo.InvariantCulture, "Function code {0} not supported.", functionCode);
					_logger.Error(errorMessage);
					throw new NotImplementedException(errorMessage);
			}

			return numBytes;
		}

		public virtual byte[] Read(int count)
		{
			byte[] frameBytes = new byte[count];
			int numBytesRead = 0;

			while (numBytesRead != count)
				numBytesRead += StreamResource.Read(frameBytes, numBytesRead, count - numBytesRead);

			return frameBytes;
		}

		internal override byte[] BuildMessageFrame(IModbusMessage message)
		{
			List<byte> messageBody = new List<byte>();
			messageBody.Add(message.SlaveAddress);
			messageBody.AddRange(message.ProtocolDataUnit);
			messageBody.AddRange(ModbusUtility.CalculateCrc(message.MessageFrame));

			return messageBody.ToArray();
		}

		internal override bool ChecksumsMatch(IModbusMessage message, byte[] messageFrame)
		{
			return BitConverter.ToUInt16(messageFrame, messageFrame.Length - 2) == BitConverter.ToUInt16(ModbusUtility.CalculateCrc(message.MessageFrame), 0);
		}

		internal override IModbusMessage ReadResponse<T>()
		{
			byte[] frameStart = Read(ResponseFrameStartLength);
			byte[] frameEnd = Read(ResponseBytesToRead(frameStart));
			byte[] frame = frameStart.Concat(frameEnd).ToArray();
			_logger.InfoFormat("RX: {0}", frame.Join(", "));

			return CreateResponse<T>(frame);
		}

		internal override byte[] ReadRequest()
		{
			byte[] frameStart = Read(RequestFrameStartLength);
			byte[] frameEnd = Read(RequestBytesToRead(frameStart));
			byte[] frame = frameStart.Concat(frameEnd).ToArray();
			_logger.InfoFormat("RX: {0}", frame.Join(", "));

			return frame;
		}
	}
}
