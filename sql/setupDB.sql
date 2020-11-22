DROP SCHEMA IF EXISTS TextGuiDB;

CREATE SCHEMA IF NOT EXISTS TextGuiDB DEFAULT CHARACTER SET utf8 ;
USE TextGuiDB;

DROP TABLE IF EXISTS TextGuiDB.MessageDisplay;
DROP TABLE IF EXISTS TextGuiDB.MessageDisplay1;
DROP TABLE IF EXISTS TextGuiDB.MessageDisplay2;
DROP TABLE IF EXISTS TextGuiDB.UpdateDisplay1;
	
CREATE TABLE IF NOT EXISTS MessageDisplay (
	Data VARCHAR(200),
	PostDate DateTime);
	
CREATE TABLE IF NOT EXISTS MessageDisplay1 (
	Data VARCHAR(200),
	PostDate DateTime);
	
CREATE TABLE IF NOT EXISTS MessageDisplay2 (
	Data VARCHAR(200),
	PostDate DateTime);
	
CREATE TABLE IF NOT EXISTS UpdateDisplay1 (
	Data VARCHAR(200),
	PostDate DateTime);

SHOW COLUMNS FROM MessageDisplay;
SHOW COLUMNS FROM MessageDisplay1;
SHOW COLUMNS FROM MessageDisplay2;
SHOW COLUMNS FROM UpdateDisplay1;

INSERT INTO MessageDisplay
	(Data, PostDate)
VALUES
	('Least Recent :D', '2000-09-19 15:43:11'),
	('Most Recent :D', '2021-09-19 15:44:32'),
	('Coffee Maker: ON', '2020-09-19 16:43:11'),
	('Plane ID: AF123: 0, 0, 0', '2020-09-19 17:43:11'),
	('Bobert''s phone', '2020-09-19 18:43:11'),
	('Bob: Hey thats my phone, IRC SERVER stuff', '2020-09-19 19:43:11'),
	('192.168.1.181 Active', '2020-09-19 20:43:11'),
	('I want to make it where if someone types a huge paragraph to me its not going to clip off the side, yet the wrap around works properly', '2022-09-19 21:43:11'),
	('OH HI DOGGY', '2030-09-19 22:43:11'),
	('2024-11-20 17:01:40\t\t\tAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa', '2024-11-20 17:01:40'),
	('2024-11-20 17:01:41\t\t\tI JUST WANT TO MAKE THIS WORK FOR LONG STRINGS, IS THAT TOO MUCH TO ASK T_T AAAAABBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa', '2024-11-20 17:01:41');

INSERT INTO MessageDisplay1
	(Data, PostDate)
VALUES
	('Least Recent :D', '2000-09-19 15:43:11'),
	('Most Recent :D', '2021-09-19 15:44:32'),
	('Plane ID: AF123: 0, 0, 0', '2020-09-19 17:43:11'),
	('Bob: Hey thats my phone, IRC SERVER stuff', '2020-09-19 19:43:11'),
	('192.168.1.181 Active', '2020-09-19 20:43:11');
	
INSERT INTO MessageDisplay2
	(Data, PostDate)
VALUES
	('OTHER Least Recent :D', '2000-09-19 15:43:11'),
	('OTHER Most Recent :D', '2021-09-19 15:44:32'),
	('Hello', '2020-09-19 16:43:11'),
	('Hi', '2020-09-19 17:43:11'),
	('LELELELELELELELLEE', '2020-09-19 18:43:11'),
	('WORDS', '2020-09-19 19:43:11'),
	('Cool', '2020-09-19 20:43:11');

INSERT INTO UpdateDisplay1
	(Data, PostDate)
VALUES
	('Coffee Maker: Up, On', '2020-09-19 16:43:11'),
	('IRC Server: Up', '2020-09-19 19:43:11'),
	('House: Currently broken into', '2030-09-19 22:43:11'),
	('HI DVA', '2029-09-19 23:43:11');

SELECT * FROM MessageDisplay;
SELECT * FROM MessageDisplay1;
SELECT * FROM MessageDisplay2;
SELECT * FROM UpdateDisplay1;
