DROP SCHEMA IF EXISTS GUIDB;

CREATE SCHEMA IF NOT EXISTS GUIDB DEFAULT CHARACTER SET utf8 ;
USE GUIDB;

DROP TABLE IF EXISTS GUIDB.HomeScreen;
DROP TABLE IF EXISTS GUIDB.TextElement;
DROP TABLE IF EXISTS GUIDB.PictureElement;
DROP TABLE IF EXISTS GUIDB.VideoElement;
DROP TABLE IF EXISTS GUIDB.StreamElement;

CREATE TABLE IF NOT EXISTS HomeScreen (
	ID INT UNSIGNED NOT NULL PRIMARY KEY,
	Type INT UNSIGNED NOT NULL,
	TypeID INT);
	
CREATE TABLE IF NOT EXISTS TextElement (
	ID INT UNSIGNED NOT NULL PRIMARY KEY,
	Data VARCHAR(200),
	Font VARCHAR(200),
	Xloc INT,
	Yloc INT);
	
CREATE TABLE IF NOT EXISTS PictureElement (
	ID INT UNSIGNED NOT NULL PRIMARY KEY,
	Data VARCHAR(200),
	Xloc INT,
	Yloc INT,
	Width INT,
	Length INT);
	
CREATE TABLE IF NOT EXISTS VideoElement (
	ID INT UNSIGNED NOT NULL PRIMARY KEY,
	Data VARCHAR(200),
	Xloc INT,
	Yloc INT,
	Width INT,
	Length INT);
	
CREATE TABLE IF NOT EXISTS StreamElement (
	ID INT UNSIGNED NOT NULL PRIMARY KEY,
	Data VARCHAR(200),
	Xloc INT,
	Yloc INT,
	Width INT,
	Length INT);

SHOW COLUMNS FROM HomeScreen;
SHOW COLUMNS FROM TextElement;
SHOW COLUMNS FROM PictureElement;
SHOW COLUMNS FROM VideoElement;
SHOW COLUMNS FROM StreamElement;

/* Types: 
	0 - Text
	1 - Picture
	2 - Video
	3 - Stream
*/
INSERT INTO HomeScreen
	(ID, Type, TypeID)
VALUES 
	(1, 0, 0),
	(2, 1, 0),
	(3, 2, 0),
	(4, 3, 0);

INSERT INTO TextElement
	(ID, Data, Font, Xloc, Yloc)
VALUES
	(0, "OH HI DOGGY", "./resources/pixantiqua.ttf", 400, 400);

INSERT INTO PictureElement
	(ID, Data, Xloc, Yloc, Width, Length)
VALUES
	(0, "./pictures/TestPic.png", 100, 100, 100, 100);

INSERT INTO VideoElement
	(ID, Data, Xloc, Yloc, Width, Length)
VALUES
	(0, "https://www.youtube.com/watch?v=0acFyeCu-po", 200, 200, 100, 100);

INSERT INTO StreamElement
	(ID, Data, Xloc, Yloc, Width, Length)
VALUES
	(0, "http://www.twitch.tv/neon_woof", 200, 400, 100, 100);

/*
INSERT INTO HomeScreen
	(ID, Type, TypeID)
VALUES 
	(1, 0, "OH HI DOGGY", 100, 100, 0, 0),
	(2, 1, "~/Pictures/TestPic.png", 100, 100, 100, 100),
	(3, 2, "https://www.youtube.com/watch?v=0acFyeCu-po", 200, 200, 100, 100),
	(3, 3, "http://www.twitch.tv/neon_woof", 200, 200, 100, 100);
*/

SELECT * FROM HomeScreen;
SELECT * FROM TextElement;
SELECT * FROM PictureElement;
SELECT * FROM VideoElement;
SELECT * FROM StreamElement;

