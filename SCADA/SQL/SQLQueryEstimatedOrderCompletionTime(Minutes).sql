USE TMCDB
GO

SELECT AVG(DATEDIFF(MINUTE, StartTime, EndTime))*(SELECT COUNT(*) FROM [TMCDB].[dbo].[Tray] WHERE [StatusID] = 1) AS 'EstimatedOrderCompletionTime(Minutes)'

FROM [Tray]

WHERE ([StatusID] = 4)