USE TMCDB
GO

SELECT TOP 1 MIN(DATEDIFF(SECOND, StartTime, EndTime)) AS 'MinimunTrayProductionTime'

FROM [Tray]

WHERE ([StatusID] = 4)