USE TMCDB
GO

SELECT (AVG(DATEDIFF(SECOND, StartTime, EndTime))) AS 'AverageTrayProductionTime(Seconds)'

FROM [Tray]

WHERE ([StatusID] = 4)