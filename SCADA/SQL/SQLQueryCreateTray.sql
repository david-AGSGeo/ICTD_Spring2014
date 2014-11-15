USE TMCDB
GO

CREATE TABLE [dbo].[Tray] (
[TrayID] INT IDENTITY NOT NULL,
[StatusID] INT NOT NULL,
[OrderID] INT,
[TimeStamp] datetime DEFAULT GETDATE(),
[TraySlot1] INT NOT NULL,
[TraySlot2] INT NOT NULL,
[TraySlot3] INT NOT NULL,
[TraySlot4] INT NOT NULL,
[TraySlot5] INT NOT NULL,
[TraySlot6] INT NOT NULL,
[TraySlot7] INT NOT NULL,
[TraySlot8] INT NOT NULL,
[RFID] INT,
[StartTime] datetime,
[EndTime] datetime,

PRIMARY KEY CLUSTERED ([TrayID] ASC),

CONSTRAINT	[FK_dbo.Tray_dbo.Tray_TraySlot1]	FOREIGN KEY	([TraySlot1])	REFERENCES	[dbo].[Colour]	([ColourID]),
CONSTRAINT	[FK_dbo.Tray_dbo.Tray_TraySlot2]	FOREIGN KEY	([TraySlot2])	REFERENCES	[dbo].[Colour]	([ColourID]),
CONSTRAINT	[FK_dbo.Tray_dbo.Tray_TraySlot3]	FOREIGN KEY	([TraySlot3])	REFERENCES	[dbo].[Colour]	([ColourID]),
CONSTRAINT	[FK_dbo.Tray_dbo.Slot_TraySlot4]	FOREIGN KEY	([TraySlot4])	REFERENCES	[dbo].[Colour]	([ColourID]),
CONSTRAINT	[FK_dbo.Tray_dbo.Slot_TraySlot5]	FOREIGN KEY	([TraySlot5])	REFERENCES	[dbo].[Colour]	([ColourID]),
CONSTRAINT	[FK_dbo.Tray_dbo.Slot_TraySlot6]	FOREIGN KEY	([TraySlot6])	REFERENCES	[dbo].[Colour]	([ColourID]),
CONSTRAINT	[FK_dbo.Tray_dbo.Slot_TraySlot7]	FOREIGN KEY	([TraySlot7])	REFERENCES	[dbo].[Colour]	([ColourID]),
CONSTRAINT	[FK_dbo.Tray_dbo.Slot_TraySlot8]	FOREIGN KEY	([TraySlot8])	REFERENCES	[dbo].[Colour]	([ColourID])
);

INSERT INTO Tray
([StatusID],[OrderID],[TraySlot1],[TraySlot2],[TraySlot3],[TraySlot4],[TraySlot5],[TraySlot6],[TraySlot7],[TraySlot8])
VALUES
(1,99,1,2,3,4,5,1,2,3);