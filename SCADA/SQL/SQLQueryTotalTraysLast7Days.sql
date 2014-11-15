USE TMCDB
GO

SELECT COUNT(*) AS 'TotalTraysLast7Days'

FROM [TMCDB].[dbo].[Tray]

WHERE ([StatusID] = 4)

AND ([EndTime] > DATEADD(DAY, -7, GETDATE()));

