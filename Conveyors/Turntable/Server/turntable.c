/* turntable.c describes functions which are executed by the turntable
*  SAMPLING OF THE IO PINS WILL BE EXECUTED USING THE BCM2835_GPIO LIBRARY
*  EVENT DETECT STATUS WILL BE USED FOR ASYNCHRONOUS READING OF THE PINS
*  LOOK UP FUNCTION:
*  -----uint8_t bcm2835_gpio_eds(uint8_t pin)-------
*/

#include "turntable.h"
#include <jansson.h>
#include <bcm2835.h>

// GPIO pins for turntable control
#define ENCODER RPI_BPLUS_GPIO_J8_15
#define SWITCH  RPI_BPLUS_GPIO_J8_13
#define MOTOR_A   RPI_BPLUS_GPIO_J8_11
#define MOTOR_B   RPI_BPLUS_GPIO_J8_12


TurnInstruction_t newTurnInstruction(TurntableCommands_t command, int rotation, int direction)
{
  TurnInstruction_t t;
  t.command = command;
  t.rotation = rotation;
  t.direction = direction;
  return t;
}

int initTurntable(Turntable_t *t)
{
  printf("initTurntable start\r\n");
  if(!bcm2835_init())
    return 1;
  // Set the pin modes
  bcm2835_gpio_fsel(MOTOR_A, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(MOTOR_B, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(ENCODER, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(ENCODER, BCM2835_GPIO_PUD_UP);
  bcm2835_gpio_fsel(SWITCH, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(SWITCH, BCM2835_GPIO_PUD_UP);
  // Initialise members
  t->maxEncoder = 0;
  t->currentEncoder = 0;
  t->encoder = 0;
  t->limitSW = 0;
  t->ttdriver = 0;
  printf("initTurntable end\r\n");
  return 0;
}


// Interprets an instruction structure and executes appropriate action on the
// given turntable object
int parseTurnInstruction(TurnInstruction_t* instruction, Turntable_t* turntable)
{
  switch(instruction->command)
  {
    case reset:
      return reset_tt(turntable);
    case calibrate:
      return calibrate_tt(turntable);
    case quarterTurn:
      return quarterTurn_tt(turntable, instruction->direction, instruction->rotation);
    case fineTurn:
      return fineTurn_tt(turntable, instruction->direction, instruction->rotation);
    default:
      return 1; // Not a recongised command
  }
}

int reset_tt(Turntable_t* turntable)
{
  printf("Start reset\r\n");
  // This function returns the turntable to its starting state
  motorStart(1);
  // Wait for reset
  while(!bcm2835_gpio_lev(SWITCH))
  {
    // Waits for falling edge
  }
  while(bcm2835_gpio_lev(SWITCH))
  {
    // waits for rising edge
  }
  motorStop();
  // Reset the turntable valus
  turntable->maxEncoder = 0;
  turntable->currentEncoder = 0;
  printf("Finish reset\r\n");
  return 0;
}

int calibrate_tt(Turntable_t* turntable)
{
  // This function must be run immediately after reset to calibrate the encoder readings
  // Reset max encoder value
  turntable->maxEncoder = 0;
  int prev_encoder = bcm2835_gpio_lev(ENCODER);
  motorStart(1);
  while(!bcm2835_gpio_lev(SWITCH))
  {
    // Waits for falling edge
    if(prev_encoder != bcm2835_gpio_lev(ENCODER))
    {
      prev_encoder = !prev_encoder;
      turntable->maxEncoder++;
    }
  }
  while(bcm2835_gpio_lev(SWITCH))
  {
    // waits for rising edge
    if(prev_encoder != bcm2835_gpio_lev(ENCODER))
    {
      prev_encoder = !prev_encoder;
      turntable->maxEncoder++;
    }
  }
  motorStop();
  // reset current encoder to start
  turntable->currentEncoder = 0;
  printf("Max encoder = %d\r\n", turntable->maxEncoder);
  return 0;
}


int quarterTurn_tt(Turntable_t* turntable, int direction, int quarters)
{
  int target = turntable->currentEncoder + (turntable->maxEncoder/4)*quarters;
  int prev_encoder = bcm2835_gpio_lev(ENCODER);
  printf("target = %d\r\ncurrentEncoder = %d\r\n",target,turntable->currentEncoder);
  motorStart(direction);
  while(target > turntable->currentEncoder)
  {
    if(prev_encoder != bcm2835_gpio_lev(ENCODER))
    {
      prev_encoder = !prev_encoder;
      turntable->currentEncoder++;
    }
    if(!bcm2835_gpio_lev(SWITCH))
    {
      if(target > turntable->maxEncoder)
      {
        target = target - turntable->maxEncoder;
        turntable->currentEncoder = 0;
        break;
      }
    }
  }
  motorStop();
  return 0;
}


int fineTurn_tt(Turntable_t* turntable, int direction, int ticks)
{
  int target = turntable->currentEncoder + ticks;
  int prev_encoder = bcm2835_gpio_lev(ENCODER);
  motorStart(direction);
  while(target > turntable->currentEncoder)
  {
    if(prev_encoder != bcm2835_gpio_lev(ENCODER))
    {
      prev_encoder = !prev_encoder;
      turntable->maxEncoder++;
    }
    if(turntable->currentEncoder > turntable->maxEncoder*3/4 && bcm2835_gpio_lev(SWITCH) == 1)
    {
      target = target - turntable->maxEncoder;
      turntable->currentEncoder = 0;
    }
  }
  motorStop();
  return 0;
}


/* JSON object for TurnInstruction looks like the following:
*  { TurnInstruction:{
*    "command":int,
*    "rotation":int,
*    "direction":int
*    }
*  }
*/

// accepts the JSON serialised string "text" and populates TurnInstruction with its data
int jsonToTurnInstruction(TurnInstruction_t* instruction, char* text)
{
  // Create JSON structures
  json_t* root;
  json_error_t error;

  // load text into JSON structure
  root = json_loads(text, 0, &error);

  // Checks for correctness
  if(!root)
  {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }

  // Gets and checks the TurnInstruction object
  json_t* turnInstruction;
  turnInstruction = json_object_get(root, "TurnInstruction");
  if(!turnInstruction)
  {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }
  if(!json_is_object(turnInstruction))
  {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }

  // Get and text the contents of the TurnInstruction object
  json_t *command, *rotation, *direction;
  command = json_object_get(turnInstruction, "command");
  if(!json_is_integer(command))
  {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }
  rotation = json_object_get(turnInstruction, "rotation");
  if(!json_is_integer(rotation))
  {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }
  direction = json_object_get(turnInstruction, "direction");
  if(!json_is_integer(direction))
  {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }

  // Populates TurnInstruction structure with the captured parameters
  instruction->command = json_integer_value(command);
  instruction->rotation = json_integer_value(rotation);
  instruction->direction = json_integer_value(direction);

  return 0;
}

void motorStart(int direction)
{
  if(direction)
  { // Forward
    bcm2835_gpio_set(MOTOR_A);
    bcm2835_gpio_clr(MOTOR_B);
  } else { // Backward
    bcm2835_gpio_set(MOTOR_B);
    bcm2835_gpio_clr(MOTOR_A);
  }
}
void motorStop()
{
  // Stop motor
  bcm2835_gpio_set(MOTOR_A);
  bcm2835_gpio_set(MOTOR_B);
}
