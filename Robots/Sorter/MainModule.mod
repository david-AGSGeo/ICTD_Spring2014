MODULE MainModule
    VAR num j:=0;
    VAR num temp := -50;
   PROC main()
        bufferPickup;
        shake; 
        sortAreaPickup;
    ENDPROC
   PROC bufferPickup()
        MoveJ SAFEPOSITION, v100, fine, tool0;
        TPWrite "Move to Intermediate Position";
        MoveJ INTERMEDIATE, v200,z100, tool0;
        TPWrite "Move to PrePickup Position";
        MoveL PREPICKUP, v200, z50, tool0;
        TPWrite "Move to Pickup Position";
        MoveL PICKUP, v100, fine, tool0;
        suction TRUE;
        TPWrite "Move to PostPickup Position";
        MoveL POSTPICKUP, v100, z50, tool0;
        TPWrite "Move to PreDrop Position";
        MoveL PREDROP, v100, z50, tool0;
        TPWrite "Move to Drop Position";
        MoveL DROP, v100, fine, tool0;
        suction FALSE;
        
        TPWrite "Move to Safe Position";
        MoveJ SAFEPOSITION, v100, fine, tool0;
   ENDPROC
    PROC shake()
        MoveJ SORTREST, v100, fine, tool0;
        
        MoveJ PRESHAKE, v100, fine, tool0;
        
        MoveJ SHAKEONE, v100, fine, tool0;
        suction TRUE;
        FOR i FROM 1 TO 5 Do
        MoveJ SHAKETWO, v800, fine, tool0;
        MoveJ SHAKEONE, v800, fine, tool0;
        ENDFOR
        suction FALSE;
        MoveJ SHAKETHREE, v100, fine, tool0;
        MoveJ SORTREST, v100, fine, tool0; 
   ENDPROC
   
   PROC sortAreaPickup()
        VAR num x;
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
        tablet :=Offs (TABLETPICKUP,-x,-y,0);
        MoveJ tablet, v100, fine, tool0;
        MoveJ Offs (tablet,0,0,-20), v100, fine, tool0;
        suction TRUE;
        MoveJ Offs (tablet,0,0,50), v100, fine, tool0;
        MoveJ Offs(BUFFERSLOT,0,(-43.5*(colour-1)),0), v100, fine, tool0;
        suction FALSE;
        TPReadFK Ans, "Continue?", "Yes", "No", stEmpty, stEmpty, stEmpty;   
       ENDWHILE

        MoveJ SORTREST, v100, fine, tool0;
    ENDPROC
ENDMODULE