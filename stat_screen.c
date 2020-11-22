//#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"

//Included for checking file update
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//-----------------

//Included for DB
#include "mariadb/mysql.h"
//#include "mysql/my_global.h"
//-----------------

//Included for string to int
#include <stdio.h>
//-----------------

#define maxBoxStringSize 180

typedef struct ReverseString {
	char* string;
	struct ReverseString * prev;
} ReverseString_t;

typedef struct TextElementStruct {
	int id;
	char* data;
	char* postdate;
	int Xloc;
	int Yloc;
	struct TextElementStruct * next;
} TextElementStruct_t;

MYSQL* connectDB() {
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) 
	{
		printf("MYSQL* connectDB()\n");
		printf("con == NULL\n");
		return NULL;
	}

	if (mysql_real_connect(con, "192.168.1.117", "GuiUser", "8smk^_4=y}vpJF7Cwdh", 
	  "TextGuiDB", 3306, NULL, 0) == NULL) 
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(con));
		return NULL;
	}
	return con;
}

void disconnectDB(MYSQL *con) {
	mysql_close(con);
}

TextElementStruct_t* queryTextElements(MYSQL *con, char* tableName) {
	if(con == NULL) {
		printf("TextElementStruct_t* queryTextElements(MYSQL *con)\n");
		printf("con == NULL\n");
		return NULL;
	}
	TextElementStruct_t* head = NULL;
	
	char* firstHalf = "SELECT * FROM ";
	char* lastHalf = " ORDER BY PostDate DESC";
	
	int firstHalfLen = strlen(firstHalf);
	int tableNameLen = strlen(tableName);
	int lastHalfLen = strlen(lastHalf);
	
	char* queryString = malloc(sizeof(char) * (firstHalfLen + tableNameLen + lastHalfLen + 1));
	
	for(int i = 0; i < firstHalfLen; i++) {
		queryString[i] = firstHalf[i];
	}
	for(int i = firstHalfLen, j = 0; j < tableNameLen; i++, j++) {
		queryString[i] = tableName[j];
	}
	for(int i = tableNameLen + firstHalfLen, j = 0; j < lastHalfLen; i++, j++) {
		queryString[i] = lastHalf[j];
	}
	queryString[firstHalfLen + tableNameLen + lastHalfLen] = '\0';

	if (mysql_query(con, queryString)) 
	{
		printf("TextElementStruct_t* queryTextElements(MYSQL *con)\n");
		printf("mysql_query(con, \"%s\")\n", queryString);
		return NULL;
	}
	
	MYSQL_RES *result = mysql_store_result(con);
	
	if (result == NULL) 
	{
		printf("TextElementStruct_t* queryTextElements(MYSQL *con)\n");
		printf("result == NULL\n");
		return NULL;
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	TextElementStruct_t* curr;
	int count = 0;
	while ((row = mysql_fetch_row(result))) 
	{ 
		//printf("TextElementStruct_t* queryTextElements(MYSQL *con)\n");
		//printf("row %i\n", count);
		if(head == NULL) {
			curr = (TextElementStruct_t *) malloc(sizeof(TextElementStruct_t));
			head = curr;
		}
		else {
			curr->next = (TextElementStruct_t *) malloc(sizeof(TextElementStruct_t));
			curr = curr->next;
		}
		//printf("ID: %s\tData: %s\tPostDate: %s\n", row[0], row[1], row[2]);
		curr->data = malloc(sizeof(char) * (strlen(row[0]) + 1));
		strcpy(curr->data, row[0]);
		curr->postdate = malloc(sizeof(char) * (strlen(row[1]) + 1));
		strcpy(curr->postdate, row[1]);
		curr->next = NULL;
		count++;
	}
	
	mysql_free_result(result);
	return head;
}

void drawTextBox(Font font, struct TextElementStruct_t* headText, char* boxTitle, int xBox, int yBox) {
	int fontSize = 20;
	int fontSpacing = 0;
	int fontLen = 15;

	int heightSpacing = 500;
	int widthSpacing = 960;
	TextElementStruct_t *currText = headText;

	Rectangle border;
	border.x = xBox;
	border.y = yBox;
	border.width = widthSpacing;//500;
	border.height = heightSpacing;//300;
	DrawRectangleLinesEx(border, 6, GRAY);

	currText = headText;
	int XlocO = xBox + 20; // + 20 to avoid the Rectangle
	int YlocO = yBox + 20; // + 20 to avoid the Rectangle

	DrawText(boxTitle, XlocO, YlocO, fontSize, RED);
	YlocO += 440;
	// count = 10
	// Print title of box
	int count = 0;

	ReverseString_t* revString = (ReverseString_t *) malloc(sizeof(ReverseString_t));
	revString->prev = NULL;

	int currTextIndex = 0;
	while(count < 22 && currText != NULL) {
		int buffIndex = 0;
		char buffString[maxBoxStringSize + 1];
		buffString[maxBoxStringSize] = '\x00';
		
		int currTextLen = strlen(currText->data);
		
		while(currTextIndex < currTextLen && buffIndex < maxBoxStringSize) {
			buffString[buffIndex] = currText->data[currTextIndex];
			buffString[buffIndex+1] = '\x00';
			Vector2 textSize = MeasureTextEx(font, buffString, fontSize, fontSpacing);
			if(textSize.x > widthSpacing-20) {
				buffString[buffIndex] = '\x00';
				break;
			}
			buffIndex++;
			currTextIndex++;
		}
		revString->string = malloc(sizeof(char) * (strlen(buffString) + 1));
		for(int i = 0; i < strlen(buffString); i++) {
			
			revString->string[i] = buffString[i];
		}
		revString->string[strlen(buffString)] = '\x00';
		ReverseString_t* tempRev = (ReverseString_t *) malloc(sizeof(ReverseString_t));
		tempRev->prev = revString;
		revString = tempRev;
		
		if(currTextIndex >= strlen(currText->data)) {
			//The string is null, so skip the first one
			revString = revString->prev;
			while(revString != NULL && count < 22) {
				if(revString->string[0] != '\0') {
					Rectangle wordLimit;
					wordLimit.x = XlocO;
					wordLimit.y = YlocO;
					wordLimit.width = border.width;
					wordLimit.height = 200;
					DrawTextRec(font, revString->string, wordLimit, fontSize, 0.0, true, BLUE);
				}
				YlocO -= 20;
				count++;
				ReverseString_t* tempDel = revString;
				revString = revString->prev;
				free(tempDel);
			}
			currText = currText->next;
			currTextIndex = 0;
			revString = (ReverseString_t *) malloc(sizeof(ReverseString_t));
			revString->prev = NULL;
		}
	}
}

int drawClock(struct tm *tm, float vcc, float hcc, float radius) {
	float hclocks = radius * sin((tm->tm_sec / 60.0) * 2.0 * 3.14159265);
	float vclocks = radius * cos((tm->tm_sec / 60.0) * 2.0 * 3.14159265);
	float hclockm = radius * sin((tm->tm_min / 60.0) * 2.0 * 3.14159265);
	float vclockm = radius * cos((tm->tm_min / 60.0) * 2.0 * 3.14159265);
	float hclockh = radius * sin((tm->tm_hour / 12.0) * 2.0 * 3.14159265);
	float vclockh = radius * cos((tm->tm_hour / 12.0) * 2.0 * 3.14159265);
	int hourNum = 0;
	for(int i = 0; i < 60; i++) {
		if(i%15 == 0) {
			DrawLine(hcc + (radius * 0.9) * sin((i / 60.0) * 2.0 * 3.14159265), 
				vcc + (radius * -0.9) * cos((i / 60.0) * 2.0 * 3.14159265), 
				hcc + radius * sin((i / 60.0) * 2.0 * 3.14159265), 
				vcc + -radius * cos((i / 60.0) * 2.0 * 3.14159265), 
				BLACK);
		}
		else if(i%5 == 0) {
			DrawLine(hcc + (radius * 0.95) * sin((i / 60.0) * 2.0 * 3.14159265), 
				vcc + (radius * -0.95) * cos((i / 60.0) * 2.0 * 3.14159265), 
				hcc + radius * sin((i / 60.0) * 2.0 * 3.14159265), 
				vcc + (radius * -1) * cos((i / 60.0) * 2.0 * 3.14159265), 
				BLACK);
		}
		else {
			DrawPixel(hcc + radius * sin((i / 60.0) * 2.0 * 3.14159265), 
				vcc + -radius * cos((i / 60.0) * 2.0 * 3.14159265), 
				BLACK);
		}
		//For all i%5 == 0, dont want to skip 15s
		if(i%5 == 0) {
			char itostr[2];
			if(i == 0) {
				hourNum = 12;
			}
			else {
				hourNum = i/5;
			}
			sprintf(itostr, "%d", hourNum);
			DrawText(itostr, 
				hcc - (5 * radius/100) + (radius * 1.2) * sin((i / 60.0) * 2.0 * 3.14159265), 
				vcc - (10 * radius/100) + -(radius * 1.2) * cos((i / 60.0) * 2.0 * 3.14159265), 
				20 * (radius/100), 
				BLUE);
		}
	}
	DrawLine(hcc, vcc, hcc + hclocks, vcc - vclocks, RED);
	DrawLine(hcc, vcc, hcc + hclockm * 0.8, vcc - vclockm * 0.8, BLUE);
	DrawLine(hcc, vcc, hcc + hclockh * 0.5, vcc - vclockh * 0.5, BLACK);

	return 0;
}

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	struct tm *tm;
	int vclockcenter = 100;
	int hclockcenter = 700;

	InitWindow(screenWidth, screenHeight, "raylib [text] example - bmfont and ttf sprite fonts loading");
	
	long sqlversion = mysql_get_client_version();
	printf("Version %ld \n", sqlversion);
	MYSQL *con = connectDB();
  
  	char* box1Table = "MessageDisplay";
  	char* box2Table = "MessageDisplay1";
  	char* box3Table = "MessageDisplay2";
  	char* box4Table = "UpdateDisplay1";
	TextElementStruct_t *box1Text = queryTextElements(con, box1Table);
	TextElementStruct_t *box2Text = queryTextElements(con, box2Table);
	TextElementStruct_t *box3Text = queryTextElements(con, box3Table);
	TextElementStruct_t *box4Text = queryTextElements(con, box4Table);
	
	bool updateScreen = false;
	
	disconnectDB(con);

	time_t now;
	time_t oldFileTime;

	time(&now);

	printf("Today is : %s", ctime(&now));
	char* msg = ctime(&now);

	Font fontBm = LoadFont("resources/pixantiqua.fnt");

	Font fontTtf = LoadFontEx("resources/pixantiqua.ttf", 32, 0, 250);
	
	char* displayTextFilePath = "DisplayText.txt";
	char* displayTextContent = LoadText(displayTextFilePath);

	SetTargetFPS(60);			   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------
	// Main game loop
	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		
		//----------------------------------------------------------------------------------
		time(&now);

		if ((tm = localtime (&now)) == NULL) {
			printf ("Error extracting time stuff\n");
			return 1;
		}

		strcpy(msg, ctime(&now));
		char* toover = "The current date/time is:\n";
		int strlento = strlen(toover);
		int strlenmsg = strlen(msg);
		char textClock[strlento+strlenmsg];
		for(int i = 0; i < strlento; i++) {
				textClock[i] = toover[i];
		}
		textClock[strlento] = '\0';
		for(int i = 0; i < strlenmsg; i++) {
				textClock[i+strlento] = msg[i];
		}
		textClock[strlenmsg+strlento] = '\0';
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);
		
		struct stat file_stat;
		int err = stat(displayTextFilePath, &file_stat);
		if (err != 0) {
			perror(" [file_is_modified] stat");
			DrawText("Sorry file broke :c", 20, 20, 20, LIGHTGRAY);
		}
		if(file_stat.st_mtime > oldFileTime) {
			displayTextContent = LoadText(displayTextFilePath);
			printf("\nDisplayText is now up to date\n");
			time(&oldFileTime);
		}
		DrawText(displayTextContent, 20, 20, 40, LIGHTGRAY);
		
		//----------- Database Updates
		if(tm->tm_sec%5 == 0) {
			if(updateScreen) {
				MYSQL *con = connectDB();	
				box1Text = queryTextElements(con, box1Table);
				box2Text = queryTextElements(con, box2Table);
				box3Text = queryTextElements(con, box3Table);
				box4Text = queryTextElements(con, box4Table);
				disconnectDB(con);
				
				updateScreen = false;
			}
		}
		else {
			updateScreen = true;
		}
		//-----------
		
		//----------- Loading Structs
		drawTextBox(fontBm, box1Text, box1Table, 0, 80);
		drawTextBox(fontBm, box2Text, box2Table, 960, 80);
		drawTextBox(fontBm, box3Text, box3Table, 0, 580);
		drawTextBox(fontBm, box4Text, box4Table, 960, 580);
		//-----------

		//drawClock(tm, vclockcenter, hclockcenter, 60.0);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadFont(fontBm);	 // AngelCode Font unloading
	UnloadFont(fontTtf);	// TTF Font unloading

	CloseWindow();				// Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
