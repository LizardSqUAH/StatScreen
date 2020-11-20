DROP SCHEMA IF EXISTS TextGuiDB;

CREATE SCHEMA IF NOT EXISTS TextGuiDB DEFAULT CHARACTER SET utf8 ;
USE TextGuiDB;

DROP TABLE IF EXISTS TextGuiDB.TestDisplay;
	
CREATE TABLE IF NOT EXISTS TestDisplay (
	ID INT UNSIGNED NOT NULL PRIMARY KEY,
	Data VARCHAR(200),
	PostDate DateTime,
	Xloc INT,
	Yloc INT);

SHOW COLUMNS FROM TestDisplay;

INSERT INTO TestDisplay
	(ID, Data, PostDate, Xloc, Yloc)
VALUES
	(0, "OH HI DOGGY0", "2020-09-19 15:43:11", 30, 20),
	(1, ":D", "2020-09-19 15:44:32", 300, 20),
	(2, "OH HI DOGGY2", "2020-09-19 16:43:11", 30, 20),
	(3, "OH HI DOGGY3", "2020-09-19 17:43:11", 30, 20),
	(4, "OH HI DOGGY4", "2020-09-19 18:43:11", 30, 20),
	(5, "OH HI DOGGY5", "2020-09-19 19:43:11", 30, 20),
	(6, "OH HI DOGGY6", "2020-09-19 20:43:11", 30, 20),
	(7, "OH HI DOGGY7", "2020-09-19 21:43:11", 30, 20),
	(8, "OH HI DOGGY8", "2020-09-19 22:43:11", 30, 20),
	(9, "OH HI DOGGY9", "2020-09-19 23:43:11", 30, 20),
	(10, "OH HI DOGGY10(noshowfor10lines)", "2020-09-20 00:43:11", 30, 20);

SELECT * FROM TestDisplay;

