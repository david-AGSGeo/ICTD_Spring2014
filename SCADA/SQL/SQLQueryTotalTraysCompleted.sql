USE TMCDB
GO

SELECT COUNT(*) AS 'TotalTraysCompleted'

FROM [TMCDB].[dbo].[Tray]

WHERE [StatusID] = 4

