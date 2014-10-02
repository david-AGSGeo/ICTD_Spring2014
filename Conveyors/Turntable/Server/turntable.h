/* This header file describes the turntable structure and its
*  functions
*  The Turntable structure represents the current status of the turntable
*  The TurnInstruction facilitated the construction of a command to move the turntable
*/

#ifndef TURNTABLE_H
#define TURNTABLE_H


// These commands
typedef enum
{
  reset = 0,
  calibrate = 1,
  quarterTurn = 2,
  fineTurn = 3
} TurntableCommands_t;

typedef struct {
  TurntableCommands_t command;
  int rotation;
  int direction;
} TurnInstruction_t;

typedef struct {
  int maxEncoder;
  int currentEncoder;
  int encoder;
  int limitSW;
  int ttdriver;
} Turntable_t;

// Structure constructor classes
TurnInstruction_t newTurnInstruction(TurntableCommands_t command, int rotation, int direction);
Turntable_t newTurntable();

// Turntable control functions
int parseTurnInstruction(TurnInstruction_t* instruction, Turntable_t* turntable);
int reset_tt(Turntable_t* turntable);
int calibrate_tt(Turntable_t* turntable);
int quarterTurn_tt(Turntable_t* turntable, int direction, int quarters);
int fineTurn_tt(Turntable_t* turntable, int direction, int ticks);
void motorStart(int direction);
void motorStop();

// JSON parsing functions
int jsonToTurnInstruction(TurnInstruction_t* instruction, char* text);


#endif
