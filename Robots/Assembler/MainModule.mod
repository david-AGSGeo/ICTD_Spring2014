MODULE MainModule

    
    PROC main()
        TPWrite "Move to Safe Position";
        MoveJ SAFEPOSITION, v100, z100, tool0;
        TPWrite "Move to PrePickup Position";
        MoveL PREPICKUP, v100, z50, tool0;
        TPWrite "Moved to Pickup Position";
        MoveL PICKUP, v100, fine, tool0;
        suction TRUE;
        TPWrite "Move to PostPickup Position";
        MoveL POSTPICKUP, v100, z100, tool0;
        TPWrite "Move to Safe Position";
        MoveL SAFEPOSITION, v100, z100, tool0;
        TPWrite "Move to PreDrop Position";
        MoveL PREDROP, v100, z50, tool0;
        TPWrite "Move to Drop Position";
        MoveL DROP, v100, fine, tool0;
        suction FALSE;
        TPWrite "Move to Safe Position";
        MoveJ SAFEPOSITION, v100, fine, tool0;
        
        !pickupTablet;
    ENDPROC
  
    
    PROC pickupTablet()
        MoveJ PREPICKUP, v100, fine, tool0;
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
