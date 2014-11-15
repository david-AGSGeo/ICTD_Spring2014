USE [TMCDB]
GO

CREATE TABLE [dbo].[Colour](
	[ColourID] INT IDENTITY (0,1) NOT NULL,
	[ColourName] NCHAR(50) NOT NULL,

	PRIMARY KEY CLUSTERED ([ColourID] ASC)

	);

	INSERT INTO Colour
	(ColourName)
	VALUES
	('Empty'),
	('Black'),
	('White'),
	('Green'),
	('Blue'),
	('Red');