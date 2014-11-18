//.NET Namespaces:
using System;
using System.Drawing;
using System.Collections;
using System.Diagnostics;
using System.Windows.Forms;
using System.Timers;

using System.IO;
using System.IO.Pipes;
using System.Text;

//VIZNET Namespaces:
using VIZNET.Shared;
using VIZNET.Shared.DataElements;
using VIZNET.Shared.DataElements.Engine;
using VIZNET.Shared.DataElements.Collections;

using VIZNET.Shared.Helpers;
using VIZNET.Shared.Interfaces;
using VIZNET.Shared.Interfaces.UI;
using VIZNET.Shared.Interfaces.Script;
using VIZNET.Shared.ScriptEngine;

namespace VIZNET.Scripting
{
   public class Script : ICodeProviderScript, INeedConnection, INeedApplication, INeedGraphicObject, INeedSpiderInfo
   {  
      private IConnection MyConnection = null;
      private IObjectManager MyApplication = null;
      private INeedController MyController = null;
      private Control MyGraphicObject = null;
      
      private Hashtable MyInputs = null;
      private Hashtable MyOutputs = null;
      
      public NamedPipeClientStream ConveyorReadPipe = null;
      public NamedPipeClientStream ConveyorWritePipe = null;
      public StreamReader ConveyorReader = null;
      public StreamWriter ConveyorWriter =  null;
      
      //---------------- Data Element Collections
      DataElementCollection AssCollection = DataElementEngine.NewDataElementCollection();
      DataElementCollection SortCollection = DataElementEngine.NewDataElementCollection();
      DataElementCollection LoadCollection = DataElementEngine.NewDataElementCollection();
      DataElementCollection UnloadCollection = DataElementEngine.NewDataElementCollection();
      DataElementCollection dbTray = DataElementEngine.NewDataElementCollection();
      DataElementCollection PLCInputs = DataElementEngine.NewDataElementCollection();
      DataElementCollection DatabaseQueries = DataElementEngine.NewDataElementCollection();
      DataElementCollection MimicCollection = DataElementEngine.NewDataElementCollection();
      DataElementCollection StartupCollection = DataElementEngine.NewDataElementCollection();
      
      //---------------- Mimic Tags
      DataElement TTQuad1 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TT_Quadrant1.value");
      DataElement TTQuad2 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TT_Quadrant2.value");
      DataElement TTQuad3 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TT_Quadrant3.value");
      DataElement TTQuad4 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TT_Quadrant4.value");
      
      //---------------- Database Query tags
      DataElement GetPendingTray = DataElementEngine.NewDataElement("Adroit.Agentgroup.DbAccess.Pending_Tray.runNow");
      DataElement TrayAssembled = DataElementEngine.NewDataElement("Adroit.Agentgroup.DbAccess.TrayAssembled.runNow");
      DataElement TrayStartTime = DataElementEngine.NewDataElement("Adroit.Agentgroup.DbAccess.TrayStartTime.runNow");
      DataElement TrayEndTime = DataElementEngine.NewDataElement("Adroit.Agentgroup.DbAccess.TrayEndTime.runNow");
      DataElement TrayScrap = DataElementEngine.NewDataElement("Adroit.Agentgroup.DbAccess.TrayScrap.runNow");
      
      //---------------- Start and Stop variables
      DataElement AssStart = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.ASSEMBLE_START.value");
      DataElement AssStop = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.ASSEMBLE_STOP.value");
      DataElement SortStart = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.SORTER_START.value");
      DataElement SortStop = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.SORTER_STOP.value");
      DataElement LoadStart = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.LOADER_START.value");
      DataElement LoadStop = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.LOADER_STOP.value");
      DataElement UnloadStart = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.UNLOADER_START.value");
      DataElement UnloadStop = DataElementEngine.NewDataElement("Adroit.Agentgroup.Digital.UNLOADER_STOP.value");
      
      
      
      //---------------- Assembler variables
      DataElement AssCommand = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.ASSEMBLE_COMMAND.value");
      DataElement AssTraySlot = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.ASSEMBLER_TRAYSLOT.value");
      DataElement AssColour = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.ASSEMBLER_TABLETBUFPOSITION.value");
      DataElement AssTabletInSlot = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.ASSEMBLE_TABLETINSLOT.value");
      DataElement AssXoffs = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.ASSEMBLE_TRAYX.value");
      DataElement AssYoffs = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.ASSEMBLE_TRAYY.value");
      DataElement AssRotation = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.ASSEMBLE_TRAYROTATION.value");
      
      //---------------- Sorter variables
      DataElement SortCommand = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.SORT_COMMAND.value");
      DataElement SortColour = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.SORTER_COLOUR.value");
      DataElement SortXoffs = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.SORTER_X.value");
      DataElement SortYoffs = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.SORTER_Y.value");
      DataElement SortTakePhoto = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.SORTER_TAKEPHOTO.value");
      DataElement SortIsScrap = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.SORTER_TABLETISSCRAP.value");
      
      //---------------- Loader variables
      DataElement LoadCommand = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.LOADER_COMMAND.value");
      DataElement LoadTrayNum = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.LOADER_TRAYNUM.value");
      
      
      //---------------- Unloader variables
      DataElement UnloadCommand = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.UNLOADER_COMMAND.value");
      DataElement UnloadDropPos = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.UNLOADER_DROPPOSITION.value");
      DataElement UnloadXoffs = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.UNLOADER_XOFFS.value");
      DataElement UnloadYoffs = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.UNLOADER_YOFFS.value");
      
      //---------------- Tray Slots
      DataElement dbTraySlot1 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_1.value");
      DataElement dbTraySlot2 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_2.value");
      DataElement dbTraySlot3 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_3.value");
      DataElement dbTraySlot4 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_4.value");
      DataElement dbTraySlot5 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_5.value");
      DataElement dbTraySlot6 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_6.value");
      DataElement dbTraySlot7 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_7.value");
      DataElement dbTraySlot8 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_SLOT_8.value");
      DataElement dbTrayOrderID = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_ORDER_ID.value");
      DataElement dbTrayStatus = DataElementEngine.NewDataElement("Adroit.Agentgroup.Integer.TRAY_STATUS_ID.value");
      
      //---------------- PLC Inputs
      DataElement TrayRack1 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_1.value");
      DataElement TrayRack2 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_2.value");
      DataElement TrayRack3 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_3.value");
      DataElement TrayRack4 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_4.value");
      DataElement TrayRack5 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_5.value");
      DataElement TrayRack6 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_6.value");
      DataElement EstopA1 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_A1_ESTOP.value");
      DataElement EstopA5 = DataElementEngine.NewDataElement("Adroit.Agentgroup.Boolean.TMC_PLC_A5_ESTOP.value");
      
      //---------------- Timers
      static System.Timers.Timer _AssTimer;
      static System.Timers.Timer _LoadTimer;
      static System.Timers.Timer _UnloadTimer;
      static System.Timers.Timer _SortTimer;
      static System.Timers.Timer _DelayTimer;
      
      //---------------- global variables
      
      int i = 0;
      int AssCounter;
      int ConvCommand;
      int CurrentTray;
      int UnloadPosition = 1;
      
      
      bool ConvConnected = false;
      bool isAssembling = false;
      bool doShake = false;
      
      int[] Order = new int[10] {0,0,0,0,0,0,0,0,0,0};
      int[,] AssBuffer = new int[5,2] {{1,0},{1,0},{0,0},{0,0},{0,0}};
      int[,] SortBuffer = new int[5,2]{{2,2},{2,2},{2,2},{2,2},{2,2}};
      int[,] TempBuffer = new int[5,2]{{0,0},{0,0},{0,0},{0,0},{0,0}};
      int[,] EmptyBuffer = new int[5,2]{{0,0},{0,0},{0,0},{0,0},{0,0}};      
      int[] PLCArray = new int[8];      
      int[,] TTArray = new int[4,2]{{0,1},{0,2},{0,3},{0,4}};
      
      //-------------- DETECTION SYSTEM VARIABLES------------------------
      
      NamedPipeClientStream detectionClient = null;
      StreamReader detectionReader = null;
      StreamWriter detectionWriter = null;
      
      bool isDetectionConnected = false;
      bool isDetectionWorking = false;
      bool tabletExists = false;
      bool isScrap = false;
      bool OrderValid = false;
      bool SystemBusy = false;
      bool RequestBuffer = false;
      bool waitingforassembler = false;
      
      
      // Define Delimiters for each string
      char[] delimiterChars = { ' ', ',', '.', ':', '\t' };

      // Buffer where return message will be stored
      string[] returnMessage;
      
      
      string status;            // The returned status based on command.
      string color;             // The returned color of tablet.
      
      string componentStatus;   // The status of tablet/tray
      int UnloadTrayoffsetX;              // The offsetX of Unload tray
      int UnloadTrayoffsetY;              // The offsetY of Unload tray
      int TrayoffsetX;              // The offsetX of tray
      int TrayoffsetY;              // The offsetY of tray
      int offsetX;              // The offsetX of tablet
      int offsetY;              // The offsetY of tablet
      
      int angle;                // The angle of tray
      
      // ORDER TEST
      int red;
      int blue;
      int black;
      int green;
      int white;
      
      StringBuilder sb = new StringBuilder();
      string priority;
      string reject = "";
      
      //entry point for script engine
      public void Main() 
      {
         //Initializes Event Handlers and Control Name Bindings
         InitializeVIZNETComponents();
         
         MimicCollection.Add(TTQuad1);
         MimicCollection.Add(TTQuad2);
         MimicCollection.Add(TTQuad3);
         MimicCollection.Add(TTQuad4);
         
         StartupCollection.Add(AssStart);
         StartupCollection.Add(AssStop);
         StartupCollection.Add(SortStart);
         StartupCollection.Add(SortStop);
         StartupCollection.Add(LoadStart);
         StartupCollection.Add(LoadStop);
         StartupCollection.Add(UnloadStart);
         StartupCollection.Add(UnloadStop);
         
         DatabaseQueries.Add(GetPendingTray);
         DatabaseQueries.Add(TrayAssembled);
         DatabaseQueries.Add(TrayStartTime);
         DatabaseQueries.Add(TrayEndTime);
         DatabaseQueries.Add(TrayScrap);
         
         AssCollection.Add(AssCommand);
         AssCollection.Add(AssTraySlot);
         AssCollection.Add(AssColour);
         AssCollection.Add(AssTabletInSlot);
         AssCollection.Add(AssXoffs);
         AssCollection.Add(AssYoffs);
         AssCollection.Add(AssRotation);
         
         LoadCollection.Add(LoadCommand);
         LoadCollection.Add(LoadTrayNum);
         
         UnloadCollection.Add(UnloadCommand);
         UnloadCollection.Add(UnloadDropPos);
         UnloadCollection.Add(UnloadXoffs);
         UnloadCollection.Add(UnloadYoffs);
         
         SortCollection.Add(SortCommand);
         SortCollection.Add(SortColour);
         SortCollection.Add(SortXoffs);
         SortCollection.Add(SortYoffs);
         SortCollection.Add(SortTakePhoto);
         SortCollection.Add(SortIsScrap);
         
                 
         dbTray.Add(dbTraySlot1);
         dbTray.Add(dbTraySlot2);
         dbTray.Add(dbTraySlot3);
         dbTray.Add(dbTraySlot4);
         dbTray.Add(dbTraySlot5);
         dbTray.Add(dbTraySlot6);
         dbTray.Add(dbTraySlot7);
         dbTray.Add(dbTraySlot8);
         dbTray.Add(dbTrayOrderID);
         dbTray.Add(dbTrayStatus);
         
         PLCInputs.Add(TrayRack1);
         PLCInputs.Add(TrayRack2);
         PLCInputs.Add(TrayRack3);
         PLCInputs.Add(TrayRack4);
         PLCInputs.Add(TrayRack5);
         PLCInputs.Add(TrayRack6);
         PLCInputs.Add(EstopA1);
         PLCInputs.Add(EstopA5);
         
         ShowBuffers();
         ShowTT();
      }
      
      
      private void StartupSequence(System.Object sender, System.EventArgs e)
      {
         PrintConsole("Initialising Robots...");
         
         AssCommand.Value = 0;
         SortCommand.Value = 0;
         LoadCommand.Value = 0;
         UnloadCommand.Value = 0;
         MyConnection.UpdateDataElements(AssCollection); 
         MyConnection.UpdateDataElements(SortCollection); 
         MyConnection.UpdateDataElements(LoadCollection); 
         MyConnection.UpdateDataElements(UnloadCollection); 
         
         /*
         AssStart.Value = 0;
         AssStop.Value = 0;
         SortStart.Value = 0;
         SortStop.Value = 0;
         LoadStart.Value = 0;
         LoadStop.Value = 0;
         UnloadStart.Value = 0;
         UnloadStop.Value = 0;
         MyConnection.UpdateDataElements(StartupCollection); 
         
         
         AssStart.Value = 1;
         SortStart.Value = 1;
         LoadStart.Value = 1;
         UnloadStart.Value = 1;
         MyConnection.UpdateDataElements(StartupCollection); 
         
         AssStart.Value = 0;
         SortStart.Value = 0;
         LoadStart.Value = 0;
         UnloadStart.Value = 0;
         MyConnection.UpdateDataElements(StartupCollection); 
         PrintConsole("Done");
         */
         
      _DelayTimer = new System.Timers.Timer(1000);
      _DelayTimer.Elapsed += new ElapsedEventHandler(_DelayTimer_Elapsed);
      _DelayTimer.Enabled = true;   
         
         
         
      }
      
      void _DelayTimer_Elapsed(object sender, ElapsedEventArgs e)
{
         _DelayTimer.Enabled = false;     
         ConveyorConnect();
         //DetectionConnect();         
         ttReset();
         LoadSortedTablet();
}
      

      private void UpdatePLC()
      {
      MethodReturnInfo info = MyConnection.ReadDataElements(PLCInputs);
      if (info.Success)
      {
         PrintConsole("Reading PLC...");
         DataElementCollection collectionReturned = info.ReturnObject as DataElementCollection;
         foreach (DataElement de in collectionReturned.Values)
         {
            
            switch(de.Name)
            {
               case "Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_1.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[0]); 
                  //PrintConsole(de.Value.ToString());
                  break;
               case "Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_2.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[1]); 
                  //PrintConsole(de.Value.ToString());
                  break;
               case "Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_3.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[2]); 
                  //PrintConsole(de.Value.ToString());
                  break;
               case "Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_4.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[3]); 
                  //PrintConsole(de.Value.ToString());
                  break;
               case "Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_5.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[4]); 
                  //PrintConsole(de.Value.ToString());
                  break;
               case "Adroit.Agentgroup.Boolean.TMC_PLC_TRAYRACK_6.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[5]); 
                  //PrintConsole(de.Value.ToString());
                  break;
               case "Adroit.Agentgroup.Boolean.TMC_PLC_A1_ESTOP.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[6]); 
                  //PrintConsole(de.Value.ToString());
                  break;
               case "Adroit.Agentgroup.Boolean.TMC_PLC_A5_ESTOP.value":
                  int.TryParse(de.Value.ToString(),out PLCArray[7]); 
                 //PrintConsole(de.Value.ToString());
                  break;
               
               default:
                  
                  break;
            }
            
         }
         string PLCName;
         for (int i = 0; i < 8; i++)
         {
            PLCName = "PLCCheckTray" + (i + 1).ToString();
            ((System.Windows.Forms.CheckBox)MyController[PLCName]).Checked = Convert.ToBoolean(PLCArray[i]);
            
         }
         PrintConsole(PLCArray[0].ToString() + PLCArray[1].ToString() +PLCArray[2].ToString() +PLCArray[3].ToString() +PLCArray[4].ToString() +PLCArray[5].ToString() +PLCArray[6].ToString() +PLCArray[7].ToString() );
         PrintConsole("PLC Read");
      }
      }

      
      private async void ttReset()
      {
         ConveyorWriter.WriteLine("Reset");
         ConveyorWriter.Flush();
         string temp = await ConveyorReader.ReadLineAsync();
         PrintConsole(temp);
         for (int i = 0; i < 4; i++)
         {
            TTArray[i,1] = i+1;
         }
         ttCalibrate();
         ShowTT();
      }
      
      private async void ttCalibrate()
      {
        ConveyorWriter.WriteLine("Calibrate");
         ConveyorWriter.Flush(); 
         string temp = await ConveyorReader.ReadLineAsync();
         PrintConsole(temp);
         for (int i = 0; i < 4; i++)
         {
            TTArray[i,1] = i+1;
         }
         LoadTray();
         ShowTT();
      }
      
      private async void ttQuarterTurn()
      {
         if (!isAssembling)
         {
         ConveyorWriter.WriteLine("QuarterTurn");
         ConveyorWriter.Flush();
         string temp = await ConveyorReader.ReadLineAsync();
         PrintConsole(temp);
         for (int i = 0; i < 4; i++)
         {
            TTArray[i,1]++;
            if (TTArray[i,1] >  4)
               TTArray[i,1] = 1;
         }
         ShowTT();
         //check if tray is present, and assemble if there is:
         AssembleCheck();
         
         LoadTray();
         unloadTray();
         }
         else
         {
            PrintConsole("Still Assembling! Quarter turn cancelled!");
         }
      }
      
      private async void btForward()
      {
         ConveyorWriter.WriteLine("BTConveyorForward");
         ConveyorWriter.Flush();
                
         
         string temp = await ConveyorReader.ReadLineAsync();
         PrintConsole(temp);
  
      }
      
      private async void btBackward()
      {
         ConveyorWriter.WriteLine("BTConveyorBackward");
         ConveyorWriter.Flush();
         string temp = await ConveyorReader.ReadLineAsync();
         PrintConsole(temp);
   
      }
      
      private void Disconnect()
      {
         ConvConnected = false;
         ConveyorWriter.WriteLine("Disconnect");
         ConveyorWriter.Flush();
         PrintConsole("Conveyors Disconnected");
      }

   private void button7_Click(System.Object sender, System.EventArgs e)
   {
      if (!ConvConnected)
      {
         PrintConsole("Conveyors Connecting...");
         ConveyorReadPipe = new NamedPipeClientStream("ConveyorWritePipe");
         ConveyorWritePipe = new NamedPipeClientStream("ConveyorReadPipe");
         ConveyorReadPipe.Connect();
         ConveyorWritePipe.Connect();
         
         ConveyorReader = new StreamReader(ConveyorReadPipe);
         ConveyorWriter = new StreamWriter(ConveyorWritePipe);
         ConvConnected = true;
         PrintConsole("Connected");
      }
   }
      
      private void ConveyorConnect()
   {
      if (!ConvConnected)
      {
         ConveyorReadPipe = new NamedPipeClientStream("ConveyorWritePipe");
         ConveyorWritePipe = new NamedPipeClientStream("ConveyorReadPipe");
         ConveyorReadPipe.Connect();
         ConveyorWritePipe.Connect();
         
         ConveyorReader = new StreamReader(ConveyorReadPipe);
         ConveyorWriter = new StreamWriter(ConveyorWritePipe);
         ConvConnected = true;
         PrintConsole("Conveyors Connected");
      }
   }
      
  

   private void ConvCombo_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      ConvCommand = (sender as ComboBox).SelectedIndex + 1;
   }

   private void button6_Click(System.Object sender, System.EventArgs e)
   {
       switch(ConvCommand)
         {
            case 1:
               ttReset();
               break;
            case 2:
               ttCalibrate();
               break;
            case 3:
               ttQuarterTurn();
               break;
            case 4:
               btForward();
               break;
            case 5:
               btBackward();
            break;
            case 6:
               Disconnect();
               break;
            default:
               break;
         }       
   }

   

   
      
      //ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER////ASSEMBLER//
 
   private void LoadTablets_Click(System.Object sender, System.EventArgs e)
   {
      
      AssCounter = 0;
      _AssTimer = new System.Timers.Timer(50);
      _AssTimer.Elapsed += new ElapsedEventHandler(_AssTimer_Elapsed);
      _AssTimer.Enabled = true;            
   }
   
      private void LoadTablets()
   {
      
      AssCounter = 0;
      _AssTimer = new System.Timers.Timer(50);
      _AssTimer.Elapsed += new ElapsedEventHandler(_AssTimer_Elapsed);
      _AssTimer.Enabled = true;            
   }
      
   private void AssembleCheck()
      {
         for (int i = 0; i < 4; i++)
         {
            if (TTArray[i,1] == 2)
            {
               if (TTArray [i,0] == 1)
               {
                     
                  if (SystemBusy)
                  {
                     AssembleCheck();
                     return;
                  }
         
                     PrintConsole("Taking Photo...");
                     sendCommand(1);
                  if (componentStatus != "valid")
                  {
                     waitingforassembler = false;
                     PrintConsole("Invalid Tray");
                     TTArray [i,0] = 4;
                     GetPendingTray.Value = false;
                     TrayAssembled.Value = false;
                     TrayStartTime.Value = false;
                     TrayEndTime.Value = false;
                     TrayScrap.Value = true;
                  
            MyConnection.UpdateDataElements(DatabaseQueries);
                     ShowTT();
                     
                     //ttQuarterTurn();
                     return;
                  }
                  else if (componentStatus == "no tray")
                  {
                     PrintConsole("No Tray");
                     TTArray [i,0] = 0;
                     ShowTT();
                     
                     //ttQuarterTurn();
                     return;
                  }
                     isAssembling = true;
                     PrintConsole("Retrieving Order...");
                     RetrieveOrder();
                     AssXoffs.Value = TrayoffsetX;
                     AssYoffs.Value = TrayoffsetY;
                     AssRotation.Value = angle;
                     LoadTablets();
                     TTArray [i,0] = 2;
                     CurrentTray = i;
                     
                     ShowTT();
                     return;
                  
               }
               else
               {
                  isAssembling = false;
                  waitingforassembler = false;
               }
            }
         }
      }
      
      private void Assemble()
      {
         //PrintConsole("Loading...");
         if (Order[AssCounter] > 0 && AssCounter <= 7)
         {
            if (AssBuffer[Order[AssCounter]-1,0] > 0)
            {
               PrintConsole("Loading from first ROW");
               AssTraySlot.Value = AssCounter + 1;
               AssColour.Value = Order[AssCounter]-1;
               AssCommand.Value = 2;
               AssTabletInSlot.Value = AssBuffer[Order[AssCounter]-1,0];
               AssBuffer[Order[AssCounter]-1,0]--;
               MyConnection.UpdateDataElements(AssCollection); 
               AssCounter++;
               _AssTimer.Start();
            }
            else if (AssBuffer[Order[AssCounter]-1,1] > 0)
            {
               PrintConsole("first ROW empty, loading from second");
               AssTraySlot.Value = AssCounter + 1;
               AssColour.Value = Order[AssCounter]+4;
               AssCommand.Value = 2;
               AssTabletInSlot.Value = AssBuffer[Order[AssCounter]-1,1];
               AssBuffer[Order[AssCounter]-1,1]--;
               MyConnection.UpdateDataElements(AssCollection); 
               AssCounter++;
               _AssTimer.Start();
            }
            
            else
            {              
               PrintConsole("No tablets of that colour");
               //STUFF HERE TO HANDLE EMPTY BUFFER
               AssCommand.Value = 1;
               MyConnection.UpdateDataElements(AssCollection);
               RequestBuffer = true;
               _AssTimer.Enabled = false;
               return;
            }
            
                             
         } 
         else if (Order[AssCounter]== 0 && AssCounter <= 7)
            {
               AssCounter++;
               _AssTimer.Start();
            }
         
         else if (AssCounter == 8)
         {
            TTArray [CurrentTray,0] = 3;
            isAssembling = false;
            GetPendingTray.Value = false;
            TrayAssembled.Value = true;
            TrayStartTime.Value = false;
            TrayEndTime.Value = false;
            TrayScrap.Value = false;
                  
            MyConnection.UpdateDataElements(DatabaseQueries);
            PrintConsole("Order Complete");
            waitingforassembler = false;
            _AssTimer.Stop();
         }
         
            
         
      }
   

void _AssTimer_Elapsed(object sender, ElapsedEventArgs e)
{
   //PrintConsole("timer elapsed");
   int test=1;
   _AssTimer.Interval = 200;
   MethodReturnInfo info = MyConnection.ReadDataElements(AssCollection);
   if (info.Success)
      {        
         DataElementCollection collectionReturned = info.ReturnObject as DataElementCollection;
                
         foreach(DataElement de in collectionReturned.Values)
         {
            //PrintConsole("checkinn Element...");
            switch(de.Name)
            {
               case "Adroit.Agentgroup.Integer.ASSEMBLE_COMMAND.value":
                  //PrintConsole("command found");
                  int.TryParse(de.Value.ToString(),out test);   
                  break;
               default:
                  break;
            }
         }
         if (test == 0) //command has been reset
         {   
            Assemble();
            ShowBuffers();
         }
       }
   else
   {
      PrintConsole("failed tag read");
   }
}
      
      
   
void _LoadTimer_Elapsed(object sender, ElapsedEventArgs e)
{
   
   int test = 1;
   MethodReturnInfo info = MyConnection.ReadDataElements(LoadCollection);
   if (info.Success)
      {        
         DataElementCollection collectionReturned = info.ReturnObject as DataElementCollection;
                
         foreach(DataElement de in collectionReturned.Values)
         {
            //PrintConsole("checkinn Element...");
            switch(de.Name)
            {
               case "Adroit.Agentgroup.Integer.LOADER_COMMAND.value":
                  //PrintConsole("command found");
                  int.TryParse(de.Value.ToString(),out test);   
                  break;
               default:
                  break;
            }
         }
         if (test == 0) //command has been reset
         {   
            ShowTT();
            if (!isAssembling && !waitingforassembler)
            {
               ttQuarterTurn();
               waitingforassembler = true;
            }
            _LoadTimer.Enabled = true; 
         }
       }
   else
   {
      PrintConsole("failed tag read");
   }
   _LoadTimer.Enabled = true; 
      //PrintConsole("Loader Timer elapsed");
}
   
   void _UnloadTimer_Elapsed(object sender, ElapsedEventArgs e)
{
    int test = 1;
      MethodReturnInfo info = MyConnection.ReadDataElements(UnloadCollection);
      if (info.Success)
      {        
         DataElementCollection collectionReturned = info.ReturnObject as DataElementCollection;
                
         foreach(DataElement de in collectionReturned.Values)
         {
            //PrintConsole("checkinn Element...");
            switch(de.Name)
            {
               case "Adroit.Agentgroup.Integer.UNLOADER_COMMAND.value":
                  //PrintConsole("command found");
                  int.TryParse(de.Value.ToString(),out test);   
                  break;
               default:
                  break;
            }
         }
         if (test == 0) //command has been reset
         {   
            
            UnloadNextTray();
             
         }
       }
   else
   {
      PrintConsole("failed tag read");
   }
}
   
   void _SortTimer_Elapsed(object sender, ElapsedEventArgs e)
{
   _SortTimer.Interval = 200;
   //PrintConsole("Sorter starting");
       int test = 1;
         
   MethodReturnInfo info = MyConnection.ReadDataElements(SortCollection);
   if (info.Success)
      {        
         DataElementCollection collectionReturned = info.ReturnObject as DataElementCollection;
                
         foreach(DataElement de in collectionReturned.Values)
         {
            //PrintConsole("checkinn Element...");
            switch(de.Name)
            {
               case "Adroit.Agentgroup.Integer.SORT_COMMAND.value":
                  //PrintConsole("command found");
                  int.TryParse(de.Value.ToString(),out test);   
                  break;
                             default:
                  break;
            }
         }
         if (test == 0) //command has been reset
         {   
            if (RequestBuffer)
            {
               _SortTimer.Enabled = false;
               btForward();
               SortCommand.Value = 1;
               TempBuffer = AssBuffer;
               AssBuffer = SortBuffer;
           
               SortBuffer = TempBuffer;
               TempBuffer = EmptyBuffer;
               ShowBuffers();
         
               MyConnection.UpdateDataElements(SortCollection);
               RequestBuffer = false;
               _SortTimer.Enabled = true;
               _AssTimer.Enabled = true;
               
            }
            else
            {
               SortNextTablet();
            }
         }
        
       }
   else
   {
      PrintConsole("failed tag read");
   }
}
   
public void LoadSortedTablet()
      {
         _SortTimer = new System.Timers.Timer(500);
         _SortTimer.Elapsed += new ElapsedEventHandler(_SortTimer_Elapsed);
         _SortTimer.Enabled = true;  
      }
      
   public void ShowBuffers()
      {
         string assName, sortName;
         for (int i = 0; i < 10; i++)
         {
            assName = "AssBuffSlot" + (i + 1).ToString();
            ((System.Windows.Forms.TextBox)MyController[assName]).Text = AssBuffer[i % 5, (int)i/5].ToString();
            sortName = "SortBuffer" + (i + 1).ToString();
            ((System.Windows.Forms.TextBox)MyController[sortName]).Text = SortBuffer[i % 5, (int)i/5].ToString();

         }
      }

   private void LoadOneTablet_Click(System.Object sender, System.EventArgs e)
   {
      AssTraySlot.Value = 1;
      AssColour.Value = Order[0];
      AssCommand.Value = 2;
      MyConnection.UpdateDataElements(AssCollection);    
   }


   private void Retrieve_Click(System.Object sender, System.EventArgs e)
   {
      GetPendingTray.Value = true;
      TrayAssembled.Value = false;
      TrayStartTime.Value = false;
      TrayEndTime.Value = false;
      TrayScrap.Value = false;
                  
      MyConnection.UpdateDataElements(DatabaseQueries);
      
      MethodReturnInfo info = MyConnection.ReadDataElements(dbTray);
      if (info.Success)
      {
         int counter = 0;
         string s = "values: ";
         DataElementCollection collectionReturned = info.ReturnObject as DataElementCollection;
         foreach (DataElement de in collectionReturned.Values)
         {
            
            switch(de.Name)
            {
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_1.value":
                  int.TryParse(de.Value.ToString(),out Order[0]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_2.value":
                  int.TryParse(de.Value.ToString(),out Order[1]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_3.value":
                  int.TryParse(de.Value.ToString(),out Order[2]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_4.value":
                  int.TryParse(de.Value.ToString(),out Order[3]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_5.value":
                  int.TryParse(de.Value.ToString(),out Order[4]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_6.value":
                  int.TryParse(de.Value.ToString(),out Order[5]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_7.value":
                  int.TryParse(de.Value.ToString(),out Order[6]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_8.value":
                  int.TryParse(de.Value.ToString(),out Order[7]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_ORDER_ID.value":
                  int.TryParse(de.Value.ToString(),out Order[8]); 
                  s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_STATUS_ID.value":
                  int.TryParse(de.Value.ToString(),out Order[9]); 
                  s += " " + de.Value.ToString();
                  break;
               default:
                  s += "666 ";
                  break;
            }
            //int.TryParse(de.Value.ToString(),out Order[counter]); 
            //s += " " + de.Value.ToString();
            //Order[counter] = de.Value.ToString();
            counter++;
         }
         PrintConsole("Order Read succeeded");
         ((System.Windows.Forms.ComboBox)MyController["Box1"]).SelectedIndex = Order[0];
      ((System.Windows.Forms.ComboBox)MyController["Box2"]).SelectedIndex = Order[1];
      ((System.Windows.Forms.ComboBox)MyController["Box3"]).SelectedIndex = Order[2];
      ((System.Windows.Forms.ComboBox)MyController["Box4"]).SelectedIndex = Order[3];
      ((System.Windows.Forms.ComboBox)MyController["Box5"]).SelectedIndex = Order[4];
      ((System.Windows.Forms.ComboBox)MyController["Box6"]).SelectedIndex = Order[5];
      ((System.Windows.Forms.ComboBox)MyController["Box7"]).SelectedIndex = Order[6];
      ((System.Windows.Forms.ComboBox)MyController["Box8"]).SelectedIndex = Order[7];
      }
      else
      {
         PrintConsole("Order Read failed");
      }
   }
   
   private void RetrieveOrder()
   {
      try            
      {   
                     GetPendingTray.Value = true;
                     TrayAssembled.Value = false;
                     TrayStartTime.Value = false;
                     TrayEndTime.Value = false;
                     TrayScrap.Value = false;
                  
                     MyConnection.UpdateDataElements(DatabaseQueries);
                     GetPendingTray.Value = false;
                     TrayAssembled.Value = false;
                     TrayStartTime.Value = true;
                     TrayEndTime.Value = false;
                     TrayScrap.Value = false;
                  
                     MyConnection.UpdateDataElements(DatabaseQueries);
      }
      catch (System.InvalidOperationException e)
         {
             PrintConsole("Exception" + e.ToString());
            OrderValid = false;
         }
      
      MethodReturnInfo info = MyConnection.ReadDataElements(dbTray);
      if (info.Success)
      {
         OrderValid = true;
         int counter = 0;
         //string s = "values: ";
         DataElementCollection collectionReturned = info.ReturnObject as DataElementCollection;
         foreach (DataElement de in collectionReturned.Values)
         {
            //MessageBox.Show(de.Name);
            switch(de.Name)
            {
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_1.value":
                  int.TryParse(de.Value.ToString(),out Order[0]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_2.value":
                  int.TryParse(de.Value.ToString(),out Order[1]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_3.value":
                  int.TryParse(de.Value.ToString(),out Order[2]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_4.value":
                  int.TryParse(de.Value.ToString(),out Order[3]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_5.value":
                  int.TryParse(de.Value.ToString(),out Order[4]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_6.value":
                  int.TryParse(de.Value.ToString(),out Order[5]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_7.value":
                  int.TryParse(de.Value.ToString(),out Order[6]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_SLOT_8.value":
                  int.TryParse(de.Value.ToString(),out Order[7]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_ORDER_ID.value":
                  int.TryParse(de.Value.ToString(),out Order[8]); 
                  //s += " " + de.Value.ToString();
                  break;
               case "Adroit.Agentgroup.Integer.TRAY_STATUS_ID.value":
                  int.TryParse(de.Value.ToString(),out Order[9]); 
                  //s += " " + de.Value.ToString();
                  break;
               default:
                  //s += "666 ";
                  break;
            }
            //int.TryParse(de.Value.ToString(),out Order[counter]); 
            //s += " " + de.Value.ToString();
            //Order[counter] = de.Value.ToString();
            counter++;
            PrintConsole("Order Read success");
         }
         //PrintConsole("Order Read");
      }
      
      
      
      ((System.Windows.Forms.ComboBox)MyController["Box1"]).SelectedIndex = Order[0];
      ((System.Windows.Forms.ComboBox)MyController["Box2"]).SelectedIndex = Order[1];
      ((System.Windows.Forms.ComboBox)MyController["Box3"]).SelectedIndex = Order[2];
      ((System.Windows.Forms.ComboBox)MyController["Box4"]).SelectedIndex = Order[3];
      ((System.Windows.Forms.ComboBox)MyController["Box5"]).SelectedIndex = Order[4];
      ((System.Windows.Forms.ComboBox)MyController["Box6"]).SelectedIndex = Order[5];
      ((System.Windows.Forms.ComboBox)MyController["Box7"]).SelectedIndex = Order[6];
      ((System.Windows.Forms.ComboBox)MyController["Box8"]).SelectedIndex = Order[7];
      
   }
      public void SortBufferPickup(System.Object sender, System.EventArgs e)
      {
         SortBuffer = TempBuffer;
         TempBuffer = EmptyBuffer;
         ShowBuffers();
      }
      
      public void AssBufferPickup(System.Object sender, System.EventArgs e)
      {
         TempBuffer = AssBuffer;
         AssBuffer = EmptyBuffer;
         ShowBuffers();
      }
      
      public void PrintConsole(string toPrint)
      {
         try
         {
            ((System.Windows.Forms.RichTextBox)MyController["OutputConsole"]).AppendText(toPrint + "\n");
         }
         catch (System.NullReferenceException e)
         {
             PrintConsole("Null Reference: " + e.ToString());
            isDetectionWorking = false;
         }
         
      }

   private void LoadTray_Click(System.Object sender, System.EventArgs e)
   {
      _LoadTimer = new System.Timers.Timer(200);
      _LoadTimer.Elapsed += new ElapsedEventHandler(_LoadTimer_Elapsed);
      _LoadTimer.Enabled = true;  
      for (int i = 0; i < 4; i++)
         {
            if (TTArray[i,1] == 1)
            {
               if (TTArray [i,0] == 0)
               {
                  int tray = getTrayFromStock();
                  PrintConsole("Tray recieved: " + tray.ToString());
                  if (tray > 0)
                  {
                     //PrintConsole("quadrant " + i.ToString());
                     LoadTrayNum.Value = tray;
                     LoadCommand.Value = 1;
                     PrintConsole("Command Sent");
                     TTArray [i,0] = 1;
                     MyConnection.UpdateDataElements(LoadCollection);
                     PrintConsole("Load into quadrant "+TTArray[i,1]+" "+i.ToString()+" "+ TTArray[i,0]);
                             
                     return;
                  }
               }
            }
         }
   }
      
      private void LoadTray()
   {
      _LoadTimer = new System.Timers.Timer(200);
      _LoadTimer.Elapsed += new ElapsedEventHandler(_LoadTimer_Elapsed);
      _LoadTimer.Enabled = true;  
      for (int i = 0; i < 4; i++)
         {
            if (TTArray[i,1] == 1)
            {
               if (TTArray [i,0] == 0)
               {
                  int tray = getTrayFromStock();
                  //PrintConsole("Tray recieved: " + tray.ToString());
                  if (tray > 0)
                  {
                     PrintConsole("Loading Tray");
                     //PrintConsole("quadrant " + i.ToString());
                     LoadTrayNum.Value = tray;
                     LoadCommand.Value = 1;
                     //PrintConsole("Command Sent");
                     TTArray [i,0] = 1;
                     MyConnection.UpdateDataElements(LoadCollection);
                     //PrintConsole("Load into quadrant "+TTArray[i,1]+" "+i.ToString()+" "+ TTArray[i,0]);
                     
                     return;
                  }
               }
            }
         }
   }
      
    private int getTrayFromStock()
      {
         UpdatePLC();
         for (int i = 0; i < 5; i++)
         {
            if(PLCArray[i] == 1)
            {
               PrintConsole("Tray slot " + (i+1).ToString());
               PrintConsole(PLCArray[i].ToString());
               return(i+1);
            }
            
         }
         PrintConsole("No trays");
         return 0;  //no trays in stock buffer
      }
      
      private void ShowTT()
      {
         string TTName;
         for (int i = 0; i < 4; i++)
         {
            
            TTName = "Quad" + TTArray[i,1].ToString();
            ((System.Windows.Forms.TextBox)MyController[TTName]).Text = TTArray[i,0].ToString();
            switch (TTArray[i,1])
            {
               case 1:
               TTQuad1.Value=TTArray[i,0];
               break;
               case 2:
               TTQuad2.Value=TTArray[i,0];
               break;
               case 3:
               TTQuad3.Value=TTArray[i,0];
               break;
               case 4:
               TTQuad4.Value=TTArray[i,0];
               break;              
            }
         }

         MyConnection.UpdateDataElements(MimicCollection);
      }

   private void unloadTray()
   {
      _UnloadTimer = new System.Timers.Timer(200);
      _UnloadTimer.Elapsed += new ElapsedEventHandler(_UnloadTimer_Elapsed);
      _UnloadTimer.Enabled = true;           
   }
      
   private void unloadTo(int position)
      {
         //PrintConsole("quadrant " + i.ToString());
                     UnloadCommand.Value = 1;
                     UnloadDropPos.Value = position;
                     PrintConsole("Command Sent");
                     TTArray [i,0] = 0;
                     MyConnection.UpdateDataElements(UnloadCollection);
                     //PrintConsole("Unload into Location "+TTArray[i,1]+" "+i.ToString()+" "+ TTArray[i,0]);
                     ShowTT();
                     return;
         }
      
      
      /////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////DETECTION SYSTEM///////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////////////////////////
      
      private void DetectionConnect()
      {
         if(!isDetectionConnected)
         {
            // Create a handler to the pipe
            try
            {
            detectionClient = new NamedPipeClientStream(
                              ".",
                              "DetectionSystem",
                              PipeDirection.InOut,
                              PipeOptions.None
                              );
            PrintConsole("Attempting to connect to pipe...");
            detectionClient.Connect();
            isDetectionWorking = true;
            PrintConsole("Connected to pipe.");
            }
            catch (System.IO.IOException e)
         {
             PrintConsole("Exception" + e.ToString());
            isDetectionWorking = false;
         }
         catch (System.NullReferenceException e)
         {
             PrintConsole("Null Reference: " + e.ToString());
            isDetectionWorking = false;
         }
            detectionReader = new StreamReader(detectionClient);
            detectionWriter = new StreamWriter(detectionClient);
            isDetectionConnected = true;
          }
         
         
      }
      
      private void writeToPipe(string message)
      {
         if (isDetectionWorking)
         {
         try
         {
         PrintConsole("Writing");
         detectionWriter.WriteLine(message);      // Write data into stream
         PrintConsole("Message Wrote: " + message);
         //PrintConsole("Flushing");
         detectionWriter.Flush();                 // Causes buffered data to be written
         //PrintConsole("Flushed");
         }
         catch (System.IO.IOException e)
         {
             PrintConsole("Exception" + e.ToString());
            isDetectionWorking = false;
         }
         catch (System.NullReferenceException e)
         {
             PrintConsole("Null Reference: " + e.ToString());
            isDetectionWorking = false;
         }
         }
      }

      private  void readFromPipe()
      {
         if (isDetectionWorking)
         {
         try
         {
         // Read return message and split the strings
         PrintConsole("Reading Detection Pipe...");
         string s =  detectionReader.ReadLine();
       
         PrintConsole("ReturnMessage: " + s);
         
         //PrintConsole("Splitting");
         returnMessage = s.Split(delimiterChars);
         }  
         catch (System.IO.IOException e)
         {
             PrintConsole("Exception" + e.ToString());
            isDetectionWorking = false;
         }
         catch (System.NullReferenceException e)
         {
             PrintConsole("Null Reference: " + e.ToString());
            isDetectionWorking = false;
         }
         }
         
      }

      private void sendCommand(int command) 
      {
         SystemBusy = true;
         switch (command)
         {
            case 0: // checkSystem
               writeToPipe("checkSystem");
               break;
            case 1: // checkTray
               writeToPipe("checkTray");
               break;
            case 2: //checkTablet
               // BUILD N WRITE
               writeToPipe("checkTablet");
               break;
            case 3: // checkProduct
               sb.Clear();
               sb.Append("checkProduct");
               if (red != 0 ) {
                  sb.Append(",");
                  sb.Append(red.ToString());
                  sb.Append(",");
                  sb.Append("Red");
               }
               if (blue != 0 ) {
                  sb.Append(",");
                  sb.Append(blue.ToString());
                  sb.Append(",");
                  sb.Append("Blue");
               }
               if (black != 0 ) {
                  sb.Append(",");
                  sb.Append(black.ToString());
                  sb.Append(",");
                  sb.Append("Black");
               }
               if (white != 0 ) {
                  sb.Append(",");
                  sb.Append(white.ToString());
                  sb.Append(",");
                  sb.Append("White");
               }
               if (green != 0 ) {
                  sb.Append(",");
                  sb.Append(green.ToString());
                  sb.Append(",");
                  sb.Append("Green");
               }
               PrintConsole(sb.ToString());
               writeToPipe(sb.ToString());
                  
               break;
            case 4: // checkProductTray
               writeToPipe("checkPTray");
               break;
            case 5: // shutdown
               writeToPipe("shutdown");
               break;
            case 6: // checkTablet,priority,color
               sb.Clear();
               sb.Append("checkTablet");
               sb.Append(",");
               sb.Append("priority");
               sb.Append(",");
               sb.Append(priority);
               PrintConsole(sb.ToString());
               writeToPipe(sb.ToString());
               break;
            case 7: // checkTablet,reject,color
               sb.Clear();
               sb.Append("checkTablet");
               sb.Append(",");
               sb.Append("reject");
               sb.Append(reject);
               PrintConsole(sb.ToString());
               writeToPipe(sb.ToString());
               break;
            case 8: // checkTablet
               sb.Clear();
               sb.Append("checkTablet");
               sb.Append(",");
               sb.Append("priority");
               sb.Append(",");
               sb.Append(priority);
               sb.Append(",");
               sb.Append("reject");
               sb.Append(reject);
               PrintConsole(sb.ToString());
               writeToPipe(sb.ToString());
               break;
            default:
               break;
         }
         readFromPipe();
         if (isDetectionWorking)
         {
            processReturnMessage(command);
         }
         SystemBusy = false;
      }
   
      // Processes the return message read from the pipe
      private void processReturnMessage(int command)
      {
         try{
         switch (command)
         {
            case 0: // checkSystem
            case 5: // shutdown
               
               status = returnMessage[0];
               break;
            
            case 1: // checkTray
               // Store Return Values into generic variables
               componentStatus = returnMessage[0];
               int.TryParse(returnMessage[1], out TrayoffsetX);
               int.TryParse(returnMessage[2], out TrayoffsetY);
               int.TryParse(returnMessage[3], out angle);
               break;
            
            case 2: //checkTablet
               if (returnMessage[0].Equals("noTablet"))
               {
                  // Unqueues the task
                  _SortTimer.Enabled = false;
                  PrintConsole(returnMessage[0]);
                  tabletExists = false;
               }
               else
               {
                  // Store Return Values into generic variables
                  componentStatus = returnMessage[0];
                  int.TryParse(returnMessage[1], out offsetX);
                  int.TryParse(returnMessage[2], out offsetY);
                  color = returnMessage[3];
                  tabletExists = true;
                  
               }
               break;
            
            case 3: // checkProduct
                 // Update Product status tag
                 // returnMessage[0] is the status
               componentStatus = returnMessage[0];
               break;
            case 4: // checkProductTray
               
               // Store Return Values into generic variables
               componentStatus = returnMessage[0];
               int.TryParse(returnMessage[1], out UnloadTrayoffsetX);
               int.TryParse(returnMessage[2], out UnloadTrayoffsetY);
               int.TryParse(returnMessage[3], out angle);
               break;
         }
         }
         catch (System.IO.IOException e)
         {
             PrintConsole("Exception" + e.ToString());
            isDetectionWorking = false;
         }
         catch (System.IndexOutOfRangeException e)
         {
             PrintConsole("Null Reference: " + e.ToString());
            isDetectionWorking = false;
         }
      }

   private void SetPriority(int tablet)
   {
      switch (tablet)
      {
         case 0:
            priority = "Red";
            break;
         case 1:
            priority = "Blue";
            break;
         case 2:
            priority = "Black";
            break;
         case 3:
            priority = "White";
            break;
         case 4:
            priority = "Green";
            break;
         default:
            break;
      }
      PrintConsole(priority);
   }
      
      private int GetColour()
      {
         isScrap = false;
      switch(color)
         {
            case "Red":
            return 1;
            case "Green":
            return 2;
            case "Blue":
            return 3;
            case "Black":
            return 4;
            case "White":
            return 5;
            default:
            isScrap = true;
            return 1;
         }
      }
      
      private void UnloadNextTray()
      {
         if (SystemBusy)
         {
            _UnloadTimer.Enabled = true;
            return;
         }
         _UnloadTimer.Enabled = false;
         DetectionConnect();
         for (int i = 0; i < 4; i++)
         {
            if (TTArray[i,1] == 4)
            {
               switch(TTArray [i,0])
               {
                  case 1:
                     PrintConsole("Empty Tray");
                  break;
                  case 2:
                  case 3:
                  case 4:
                  case 5:
                
                     PrintConsole("Getting coords of unload tray");
                     sendCommand(4);
                     UnloadXoffs.Value = UnloadTrayoffsetX;
                     UnloadYoffs.Value = UnloadTrayoffsetY;
                     PrintConsole("Unloading Product");
                     unloadTo(UnloadPosition);
                  UnloadPosition++;
                  if (UnloadPosition >6)
                     UnloadPosition = 1;
                  GetPendingTray.Value = false;
                  TrayAssembled.Value = false;
                  TrayStartTime.Value = false;
                  TrayEndTime.Value = true;
                  TrayScrap.Value = false;
                  
                  MyConnection.UpdateDataElements(DatabaseQueries);
                  
                  break;
               }
               
            }
         }
      }
      
      private void SortNextTablet()
      {
         if (SystemBusy)
         {
            _SortTimer.Enabled = true; 
            return;
         }
         _SortTimer.Enabled = false; 
         DetectionConnect();
         sendCommand(2);
         //bool isScrap = ((System.Windows.Forms.CheckBox)MyController["IsScrap"]).Checked;
       
         ShowBuffers();
         
         PrintConsole("checking tablets...");
         
         
         int colour = GetColour();
         
         if (SortBuffer[colour-1,0] < 8)
            SortBuffer[colour-1,0]++;
         else if (SortBuffer[colour-1,1] < 8)
         {
            SortBuffer[colour-1,1]++;
            colour += 5;
         }
         else 
         {
            PrintConsole("colour full");
            _SortTimer.Enabled = true;
            return;
         }
         
         if (tabletExists)
         {
            doShake = false;
            SortXoffs.Value = offsetX;
            SortYoffs.Value = offsetY;
            SortColour.Value = colour;
            SortIsScrap.Value = isScrap;
            SortCommand.Value = 3;
            MyConnection.UpdateDataElements(SortCollection);  
             _SortTimer.Enabled = true;
         }
         else
            {
               if (!doShake)
               {
                     doShake = true;
                  PrintConsole("Shaking...");
                   SortCommand.Value = 2;
                    MyConnection.UpdateDataElements(SortCollection);
                     _SortTimer.Enabled = true;  
               } 
               else
                PrintConsole("No Tablets in stock");
            }
        
      }

   
      
/***************************************************************************************************************************
      **********************************************************************************************************************
      **********************************************************************************************************************/      
      private void Box1_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[0] = (sender as ComboBox).SelectedIndex ;
   }

   private void Box2_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[1] = (sender as ComboBox).SelectedIndex ;
   }

   private void Box3_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[2] = (sender as ComboBox).SelectedIndex ;
   }

   private void Box4_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[3] = (sender as ComboBox).SelectedIndex ;
   }

   private void Box5_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[4] = (sender as ComboBox).SelectedIndex ;
   }

   private void Box6_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[5] = (sender as ComboBox).SelectedIndex ;
   }

   private void Box7_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[6] = (sender as ComboBox).SelectedIndex ;
   }

   private void Box8_SelectionChangeCommitted(System.Object sender, System.EventArgs e)
   {
      Order[7] = (sender as ComboBox).SelectedIndex ;
   }
   

   private void Reset_Robots_Click(System.Object sender, System.EventArgs e)
   {
         AssCommand.Value = 0;
         SortCommand.Value = 0;
         LoadCommand.Value = 0;
         UnloadCommand.Value = 0;
         MyConnection.UpdateDataElements(AssCollection); 
         MyConnection.UpdateDataElements(SortCollection); 
         MyConnection.UpdateDataElements(LoadCollection); 
         MyConnection.UpdateDataElements(UnloadCollection); 
      
      if (_AssTimer != null)
      _AssTimer.Enabled = false;
      if (_SortTimer != null)
      _SortTimer.Enabled = false;
      if (_LoadTimer != null)
      _LoadTimer.Enabled = false;
      if (_UnloadTimer != null)
      _UnloadTimer.Enabled = false;    
   } 

      #region VIZNET Generated Code
      
         #region IHost Members
         //INeedApplication Members      
         public IObjectManager Application
         {
            get   {return MyApplication;}
            set   {MyApplication=value;}
         }
         
         //INeedConnection Members
         public IConnection Connection
         {
            get   {return MyConnection;}
            set   {MyConnection=value;}
         }
         
         //INeedGraphicObject Members
         public System.Windows.Forms.Control Control
         {
            get   {return MyGraphicObject;}
            set   {MyGraphicObject=value;}
         }
         
         public VIZNET.Shared.Interfaces.INeedController Controller
         {
            get   {  return MyController;   }
            set   {  MyController = value;  }
         }      

         //INeedSpiderInfo Members
         public Hashtable Inputs
         {
            get   {  return MyInputs;   }
            set   {  MyInputs = value;  }
         }  
         public Hashtable Outputs
         {
            get   {  return MyOutputs;   }
            set   {  MyOutputs = value;  }
         }  
         #endregion  
            
      //Initializes Event Handlers and Control Name Bindings
      public void InitializeVIZNETComponents()
      {
      ((System.Windows.Forms.Button)MyController["Reset_Robots"]).Click += new System.EventHandler(this.Reset_Robots_Click);
            
      ((System.Windows.Forms.Button)MyController["LoadTray"]).Click += new System.EventHandler(this.LoadTray_Click);
      ((System.Windows.Forms.Button)MyController["Retrieve"]).Click += new System.EventHandler(this.Retrieve_Click);
      ((System.Windows.Forms.Button)MyController["LoadOneTablet"]).Click += new System.EventHandler(this.LoadOneTablet_Click);
      ((System.Windows.Forms.Button)MyController["LoadTablets"]).Click += new System.EventHandler(this.LoadTablets_Click);
      ((System.Windows.Forms.ComboBox)MyController["Box8"]).SelectionChangeCommitted += new System.EventHandler(this.Box8_SelectionChangeCommitted);
      ((System.Windows.Forms.ComboBox)MyController["Box7"]).SelectionChangeCommitted += new System.EventHandler(this.Box7_SelectionChangeCommitted);
      ((System.Windows.Forms.ComboBox)MyController["Box6"]).SelectionChangeCommitted += new System.EventHandler(this.Box6_SelectionChangeCommitted);
      ((System.Windows.Forms.ComboBox)MyController["Box5"]).SelectionChangeCommitted += new System.EventHandler(this.Box5_SelectionChangeCommitted);
      ((System.Windows.Forms.ComboBox)MyController["Box4"]).SelectionChangeCommitted += new System.EventHandler(this.Box4_SelectionChangeCommitted);
      ((System.Windows.Forms.ComboBox)MyController["Box3"]).SelectionChangeCommitted += new System.EventHandler(this.Box3_SelectionChangeCommitted);
      ((System.Windows.Forms.ComboBox)MyController["Box2"]).SelectionChangeCommitted += new System.EventHandler(this.Box2_SelectionChangeCommitted);
      ((System.Windows.Forms.ComboBox)MyController["Box1"]).SelectionChangeCommitted += new System.EventHandler(this.Box1_SelectionChangeCommitted);
      ((System.Windows.Forms.Button)MyController["button6"]).Click += new System.EventHandler(this.button6_Click);
      ((System.Windows.Forms.ComboBox)MyController["ConvCombo"]).SelectionChangeCommitted += new System.EventHandler(this.ConvCombo_SelectionChangeCommitted);
      ((System.Windows.Forms.Button)MyController["ConvConnect"]).Click += new System.EventHandler(this.button7_Click);
      
      ((System.Windows.Forms.Button)MyController["SortBufferPickup"]).Click += new System.EventHandler(this.SortBufferPickup);
      ((System.Windows.Forms.Button)MyController["AssBufferPickup"]).Click += new System.EventHandler(this.AssBufferPickup);
         ((System.Windows.Forms.Button)MyController["STARTUP"]).Click += new System.EventHandler(this.StartupSequence);
      }
      
      #endregion
   }
}