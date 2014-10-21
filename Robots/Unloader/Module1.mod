MODULE Module1
VAR num TRAYOFFSET:= -90;
PERS num Command ;
PERS num trayNum;

PROC main()
     trayNum:=1;
     WHILE Command >= 0 DO
             IF Command = 0 THEN
               WaitTime 1.0;
               TPWrite "Waiting...";
             ELSEIF Command = 1 THEN
                pickupTray;
             ENDIF     
        ENDWHILE
    
ENDPROC
PROC pickupTray()
VAR robtarget trayPos;
     IF trayNum = 6 THEN
         trayPos := TRAY1;
     ELSEIF trayNum = 5 THEN
         trayPos := TRAY2;
     ELSEIF trayNum = 4 THEN
         trayPos := TRAY3;
     ELSEIF trayNum = 3 THEN
        trayPos := TRAY4;
     ELSEIF trayNum = 2 THEN
         trayPos := TRAY5;
     ELSE
          trayPos := TRAY6;
     ENDIF
        
     
	 MoveJ offs(TRAY1,0,-120,0), v100, fine, tool0;
     MoveJ Offs(trayPos,0,-120,0), v100, fine, tool0;
     MoveJ trayPos, v100, fine, tool0; 
     suction TRUE;
     MoveJ Offs(trayPos,0,-120,0), v100, fine, tool0;
     MoveJ LOADERDROP, v100, fine, tool0;
     MoveJ Offs(LOADERDROP,0,-222,-166),v100, fine, tool0;
     MoveJ Offs(LOADERDROP,0,-248,-200),v100, fine, tool0;
     suction FALSE;
     Movel Offs(LOADERDROP,0,-80,-200),v100, fine, tool0;
     
ENDPROC
ENDMODULE