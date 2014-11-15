USE TMCDB
GO

SELECT COUNT(*) AS 'TotalTraysLast24Hours'

FROM [TMCDB].[dbo].[Tray]

WHERE ([StatusID] = 4)

AND ([EndTime] > DATEADD(HOUR, -24, GETDATE()));

