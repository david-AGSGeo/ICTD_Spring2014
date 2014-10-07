MODULE SuctionControl
    PROC suction(bool enabled)
        IF enabled = TRUE THEN
            WaitTime 0.5;
            TPWrite "suction On";
            Set DO10_6;
            WaitTime 0.5;
            
        ELSE
            WaitTime 0.5;
            TPWrite "suction Off";
            Reset DO10_6;
            WaitTime 0.5;

        ENDIF
    ENDPROC
ENDMODULE