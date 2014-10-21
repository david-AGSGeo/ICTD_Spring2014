MODULE SuctionControl
    PROC suction(bool enabled)
        IF enabled = TRUE THEN
            WaitTime 0.5;
            TPWrite "suction On";
            Reset DO10_4;
            Set DO10_5;
            WaitTime 0.5;
            
        ELSE
            WaitTime 0.5;
            TPWrite "suction Off";
            Reset DO10_5;
            Set DO10_4;
            WaitTime 0.5;

        ENDIF
    ENDPROC
ENDMODULE