USE TMCDB
GO

SELECT TOP 1 DATEDIFF(SECOND, StartTime, EndTime) AS 'LastTrayProductionTime'

FROM [Tray]

WHERE ([StatusID] = 4)

ORDER BY [EndTime] DESC
