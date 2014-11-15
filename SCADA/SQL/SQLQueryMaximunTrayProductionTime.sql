USE TMCDB
GO

SELECT TOP 1 MAX(DATEDIFF(SECOND, StartTime, EndTime)) AS 'MaximunTrayProductionTime'

FROM [Tray]

WHERE ([StatusID] = 4)