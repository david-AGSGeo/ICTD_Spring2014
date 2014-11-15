USE [TMCDB]
GO

CREATE TABLE [dbo].[Status](
	[StatusID] INT IDENTITY (1,1) NOT NULL,
	[StatusName] NCHAR(50) NOT NULL,

	PRIMARY KEY CLUSTERED ([StatusID] ASC)

	);

	INSERT INTO Status
	(StatusName)
	VALUES
	('Valid'),
	('Scrap'),
	('Reject'),
	('Complete');