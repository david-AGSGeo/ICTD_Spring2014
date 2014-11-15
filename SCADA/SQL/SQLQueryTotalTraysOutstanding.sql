USE TMCDB
GO

SELECT COUNT(*) AS 'TotalTraysOutstanding'

FROM [TMCDB].[dbo].[Tray]

WHERE [StatusID] = 1

