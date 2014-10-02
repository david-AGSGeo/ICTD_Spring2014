using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Turntable_Instruction_Handler
{
    enum command { reset = 0, calibrate = 1, quarter = 2, fineTurn = 3 };
    class TurnInstruction
    {
        public command command { get; set; }
        public int rotation { get; set; }
        public int direction { get; set; }

        public string turnInstructionToJSON(TurnInstruction t)
        {
            return JsonConvert.SerializeObject(t);
        }
    }
}
