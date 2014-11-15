USE TMCDB
GO

SELECT 100 * COUNT(*)  / ((SELECT COUNT(*) FROM [Tray] WHERE [StatusID] = 4) + COUNT(*) + (SELECT COUNT(*) FROM [RejectTray])) AS 'PercentageOfScrapTrays'

FROM [ScrapTray]