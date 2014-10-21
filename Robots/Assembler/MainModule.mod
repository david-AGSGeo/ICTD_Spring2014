MODULE MainModule
 PERS num Command:=0;
    
    PROC main()
             IF Command = 0 THEN
               WaitTime 1.0;
               TPWrite "Waiting...";
             ELSEIF Command = 1 THEN
                bufferPickup; 
             ENDIF     
    ENDPROC
  
   PROC bufferPickup()
        TPWrite "Move to Safe Position";
        MoveJ SAFEPOSITION, v100, z100, tool0;
        TPWrite "Move to PrePickup Position";
        MoveL Offs(PICKUP,0,0,20), v100, z50, tool0;
        TPWrite "Moved to Pickup Position";
        MoveL PICKUP, v100, fine, tool0;
        suction TRUE;
        TPWrite "Move to PostPickup Position";
        MoveL Offs(PICKUP,0,0,100), v100, z100, tool0;
        TPWrite "Move to Safe Position";
        MoveL SAFEPOSITION, v100, z100, tool0;
        TPWrite "Move to PreDrop Position";
        MoveL Offs(DROP,0,0,50), v100, z50, tool0;
        TPWrite "Move to Drop Position";
        MoveL DROP, v100, fine, tool0;
        suction FALSE;
        TPWrite "Move to Safe Position";
        MoveJ SAFEPOSITION, v100, fine, tool0;
        Command:=0;
   ENDPROC 
   
    PROC pickupTablet()
        MoveJ Offs(PICKUP,0,0,20), v100, fine, tool0;
        MoveL TABLETPOS1, v100, fine, tool0;
        MoveL TABLETPOS2, v100, fine, tool0;
        MoveL TABLETPOS3, v100, fine, tool0;
        MoveL TABLETPOS4, v100, fine, tool0;
        MoveL TABLETPOS5, v100, fine, tool0;
        MoveL TABLETPOS6, v100, fine, tool0;
        MoveL TABLETPOS7, v100, fine, tool0;
        MoveL TABLETPOS8, v100, fine, tool0;
        MoveL SAFEPOSITION, v100, z100, tool0;
        
    ENDPROC
ENDMODULE
