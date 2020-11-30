DROP SCHEMA IF EXISTS TextGuiDB;

CREATE SCHEMA IF NOT EXISTS TextGuiDB DEFAULT CHARACTER SET utf8 ;
USE TextGuiDB;

DROP TABLE IF EXISTS TextGuiDB.MessageDisplay;
DROP TABLE IF EXISTS TextGuiDB.MessageDisplay1;
DROP TABLE IF EXISTS TextGuiDB.MessageDisplay2;
DROP TABLE IF EXISTS TextGuiDB.UpdateDisplay1;
	
CREATE TABLE IF NOT EXISTS MessageDisplay (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
	Title VARCHAR(200),
	Data VARCHAR(200),
	PostDate DateTime);
	
CREATE TABLE IF NOT EXISTS MessageDisplay1 (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
	Title VARCHAR(200),
	Data VARCHAR(200),
	PostDate DateTime);
	
CREATE TABLE IF NOT EXISTS MessageDisplay2 (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
	Title VARCHAR(200),
	Data VARCHAR(200),
	PostDate DateTime);
	
CREATE TABLE IF NOT EXISTS UpdateDisplay1 (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
	Title VARCHAR(200),
	Data VARCHAR(200),
	PostDate DateTime);

SHOW COLUMNS FROM MessageDisplay;
SHOW COLUMNS FROM MessageDisplay1;
SHOW COLUMNS FROM MessageDisplay2;
SHOW COLUMNS FROM UpdateDisplay1;

INSERT INTO MessageDisplay
	(ID, Title, Data, PostDate)
VALUES
	(1, 'Title', 'Least Recent :D', '2000-09-19 15:43:11'),
	(2, 'Title', 'Most Recent :D', '2021-09-19 15:44:32'),
	(3, 'Title', 'Coffee Maker: ON', '2020-09-19 16:43:11'),
	(4, 'Title', 'Plane ID: AF123: 0, 0, 0', '2020-09-19 17:43:11'),
	(5, 'Title', 'Bobert''s phone', '2020-09-19 18:43:11'),
	(6, 'Title', 'Bob: Hey thats my phone, IRC SERVER stuff', '2020-09-19 19:43:11'),
	(7, 'Title', '192.168.1.181 Active', '2020-09-19 20:43:11'),
	(8, 'Title', 'I want to make it where if someone types a huge paragraph to me its not going to clip off the side, yet the wrap around works properly', '2022-09-19 21:43:11'),
	(9, 'Title', 'OH HI DOGGY', '2030-09-19 22:43:11'),
	(10, 'Title', 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa', '2024-11-20 17:01:40'),
	(11, 'Title', 'I JUST WANT TO MAKE THIS WORK FOR LONG STRINGS, IS THAT TOO MUCH TO ASK T_T AAAAABBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa', '2024-11-20 17:01:41');

INSERT INTO MessageDisplay1
	(ID, Title, Data, PostDate)
VALUES
	(1, 'Title', 'Least Recent :D', '2000-09-19 15:43:11'),
	(2, 'Title', 'Most Recent :D', '2021-09-19 15:44:32'),
	(3, 'Title', 'Plane ID: AF123: 0, 0, 0', '2020-09-19 17:43:11'),
	(4, 'Title', 'Bob: Hey thats my phone, IRC SERVER stuff', '2020-09-19 19:43:11'),
	(5, 'Title', '192.168.1.181 Active', '2020-09-19 20:43:11');
	
INSERT INTO MessageDisplay2
	(ID, Title, Data, PostDate)
VALUES
	(1, 'Title', 'OTHER Least Recent :D', '2000-09-19 15:43:11'),
	(2, 'Title', 'OTHER Most Recent :D', '2021-09-19 15:44:32'),
	(3, 'Title', 'Hello', '2020-09-19 16:43:11'),
	(4, 'Title', 'Hi', '2020-09-19 17:43:11'),
	(5, 'Title', 'LELELELELELELELLEE', '2020-09-19 18:43:11'),
	(6, 'Title', 'WORDS', '2020-09-19 19:43:11'),
	(7, 'Title', 'Cool', '2020-09-19 20:43:11');

/*INSERT INTO UpdateDisplay1
	(ID, Title, Data, PostDate)
VALUES
	(1, 'Title', 'Coffee Maker: Up, On', '2020-09-19 16:43:11'),
	(2, 'Title', 'IRC Server: Up', '2020-09-19 19:43:11'),
	(3, 'Title', 'House: Currently broken into', '2030-09-19 22:43:11'),
	(4, 'Title', 'HI DVA', '2029-09-19 23:43:11');
*/
SELECT * FROM MessageDisplay;
SELECT * FROM MessageDisplay1;
SELECT * FROM MessageDisplay2;
SELECT * FROM UpdateDisplay1;
