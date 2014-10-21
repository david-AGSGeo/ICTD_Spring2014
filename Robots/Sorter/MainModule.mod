MODULE MainModule
    VAR num j:=0;
    VAR num temp := -50;
    PERS num Command:=0;!
    PERS num x; ! input of x coordinates for sort grid.
    PERS num y; ! input of y coordinates for sort gird.
    PERS num colour; ! input of colour of tablet for sorting process.
       
   PROC main() ! program that runs on SCADA to receive command for various modes
             IF Command = 0 THEN
               WaitTime 1.0;
               TPWrite "Waiting...";
             ELSEIF Command = 1 THEN ! when it receives 1 it runs bufferPickup
                bufferPickup; 
             ELSEIF Command = 2 THEN ! when it recieves 2 it runs shake
               shake;   
             ELSEIF Command = 3 THEN ! when it receives 3 it runs sortAreaPickup
                sortAreaPickup; 
             ENDIF     
    ENDPROC
    
   PROC bufferPickup() ! Picks up the buffer
        MoveJ SAFEPOSITION, v100, fine, tool0; ! Moves to SAFEPOSITION to pickup the buffer from BUFFER Zone
        TPWrite "Move to PrePickup Position"; ! Print the string on to Flexipendant
        MoveL Offs(PICKUP,0,0,20), v100, z50, tool0; ! Moves and Lowers Robot head to top of Buffer in BUFFER Zone
        TPWrite "Move to Pickup Position"; ! Prints the string on to Flexipendant
        MoveL PICKUP, v100, fine, tool0; ! lowers the Head of Robot
        suction TRUE; ! Picks up the buffer
        TPWrite "Move to PostPickup Position"; ! Prints the string on to Flexipendant
        MoveL Offs(PICKUP,0,0,50), v100, z50, tool0; ! Picks up the Buffer
        TPWrite "Move to PreDrop Position"; ! Prints the string on to Flexipendant
        MoveL Offs(DROP,0,0,115), v100, z50, tool0; ! Moves the picked buffer to drop postion on conveyor belt
        TPWrite "Move to Drop Position"; ! Prints the string to Flexipendant
        MoveL DROP, v100, fine, tool0; ! Lowers the head on conveyor belt
        suction FALSE; ! Release the Buffer
        
        TPWrite "Move to Safe Position"; ! Prints the string to Flexipendant
        MoveJ SAFEPOSITION, v100, fine, tool0; ! Move the Robot Head into initial SAFEPOSITION
        Command := 0; ! resets the mode to 0
   ENDPROC
   
    PROC shake() ! Shakes the tablet in the Sorting Grid (sorting box)
        MoveJ SORTREST, v100, fine, tool0; ! 
        MoveJ PRESHAKE, v100, fine, tool0; ! 
        MoveJ SHAKEONE, v100, fine, tool0; ! 
        suction TRUE;
        FOR i FROM 1 TO 2 Do
        MoveJ SHAKETWO, v800, fine, tool0;
        MoveJ SHAKEONE, v800, fine, tool0;
        ENDFOR
        suction FALSE;
        MoveJ SORTREST, v100, fine, tool0; 
        Command := 0; ! resets the mode to 0
   ENDPROC
   
    
   PROC sortAreaPickup() ! Picks up the Tablet from Sorting area to Buffer on Bluetooth Tray.

        VAR robtarget tablet;
        MoveJ SORTREST, v100, fine, tool0; ! Initial position for robot before sorting
        MoveJ PRETABLETPICKUP, v100, fine, tool0; ! Intermediate position before pickup (Intermedite coordinates of Trajectory to TABLEPICKUP position) (changes the angle of the head)
        MoveJ TABLETPICKUP, v100, fine, tool0; ! Initial Position for Tablet Pickup in Sort Area (moves up and down slightly)
        tablet :=Offs (TABLETPICKUP,-x,-y,30); ! Receives the inputs from SCADA (Initiate the Program)
        MoveJ tablet, v100, fine, tool0; ! Program starts for pick up from sorting Area
        MoveJ Offs (tablet,0,0,-50), v100, fine, tool0; ! Moves to position according to input from SCADA
        suction TRUE; ! Pull the tablet
        MoveJ Offs (tablet,0,0,50), v100, fine, tool0; ! Moves the head position according to input from SCADA
        MoveJ Offs(BUFFERSLOT,0,(-43.5*(colour-1)),20), v100, fine, tool0; ! Moves the initial Buffer position
        MoveJ Offs(BUFFERSLOT,0,(-43.5*(colour-1)),0), v100, fine, tool0; ! Moves the head down
        suction FALSE; ! drops the tablet into buffer slot
        MoveJ Offs(BUFFERSLOT,0,(-43.5*(colour-1)),20), v100, fine, tool0; ! Moves the head to initial buffer position
        MoveJ SORTREST, v100, fine, tool0; ! Move back to SORTREST position
        Command := 0; ! resets the mode to 0
    ENDPROC
   
   PROC sortAreaPickupOld()
        VAR num x; ! 
        VAR num y;
        VAR num colour;
        VAR num Ans := 1 ;
        VAR robtarget tablet;
        MoveJ SORTREST, v100, fine, tool0;
        MoveJ PRETABLETPICKUP, v100, fine, tool0;
        MoveJ TABLETPICKUP, v100, fine, tool0; 
       WHILE Ans = 1  DO
        TPReadNum x, "Enter x";
        TPReadNum y, "Enter y";
        TPReadFK colour, "Tablet Colour", "Blue", "Red",stEmpty , "White", "Black"; 
        tablet :=Offs (TABLETPICKUP,-x,-y,30);
        MoveJ tablet, v100, fine, tool0;
        MoveJ Offs (tablet,0,0,-50), v100, fine, tool0;
        suction TRUE;
        MoveJ Offs (tablet,0,0,50), v100, fine, tool0;
        MoveJ Offs(BUFFERSLOT,0,(-43.5*(colour-1)),20), v100, fine, tool0;
        MoveJ Offs(BUFFERSLOT,0,(-43.5*(colour-1)),0), v100, fine, tool0;
        suction FALSE;
        MoveJ Offs(BUFFERSLOT,0,(-43.5*(colour-1)),20), v100, fine, tool0;
        TPReadFK Ans, "Continue?", "Yes", "No", stEmpty, stEmpty, stEmpty;   
       ENDWHILE

        MoveJ SORTREST, v100, fine, tool0;
        Command := 0;
    ENDPROC
ENDMODULE