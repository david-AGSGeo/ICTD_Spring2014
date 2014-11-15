USE [TMCDB]
GO

CREATE TABLE [dbo].[RejectTray](
	[RejectID] INT IDENTITY (1,1) NOT NULL,
	[TimeStamp] DATETIME DEFAULT GETDATE(),

	);

	INSERT INTO RejectTray
	(TimeStamp)
	VALUES
	(GETDATE());