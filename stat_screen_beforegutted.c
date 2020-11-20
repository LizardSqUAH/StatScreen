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

typedef struct TextElementStruct {
	char* data;
	char* font;
	int Xloc;
	int Yloc;
	struct TextElementStruct * next;
} TextElementStruct_t;

typedef struct PictureElementStruct {
	char* data;
	int Xloc;
	int Yloc;
	int Width;
	int Length;
	struct PictureElementStruct * next;
} PictureElementStruct_t;

typedef struct ImageStruct {
	Image image;
	Texture2D texture;
	int Xloc;
	int Yloc;
	int Width;
	int Length;
	struct ImageStruct * next;
} ImageStruct_t;

MYSQL* connectDB() {
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) 
	{
		return NULL;
	}

	if (mysql_real_connect(con, "192.168.1.118", "GuiUser", "8smk^_4=y}vpJF7Cwdh", 
	  "GUIDB", 0, NULL, 0) == NULL) 
	{
		return NULL;
	}
	return con;
}

void disconnectDB(MYSQL *con) {
	mysql_close(con);
}

TextElementStruct_t* queryTextElements(MYSQL *con) {
	if(con == NULL) {
		return NULL;
	}
	TextElementStruct_t* head = NULL;//{ 0, 0, 0, 0, NULL };

	if (mysql_query(con, "SELECT * FROM HomeScreen A LEFT OUTER JOIN TextElement B ON A.TypeID = B.ID WHERE A.Type=0")) 
	{
		return NULL;
	}
	
	MYSQL_RES *result = mysql_store_result(con);
	
	if (result == NULL) 
	{
		return NULL;
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	TextElementStruct_t* curr;
	while ((row = mysql_fetch_row(result))) 
	{ 
		if(head == NULL) {
			//printf("\nHead is null, first item in list\n");
			curr = (TextElementStruct_t *) malloc(sizeof(TextElementStruct_t));
			head = curr;
		}
		else {
			//printf("\nHead is not null\n");
			curr->next = (TextElementStruct_t *) malloc(sizeof(TextElementStruct_t));
			curr = curr->next;
		}
		curr->data = malloc(sizeof(char) * (strlen(row[4]) + 1));
		strcpy(curr->data, row[4]);
		curr->font = malloc(sizeof(char) * (strlen(row[5]) + 1));
		strcpy(curr->font, row[5]);
		sscanf(row[6], "%i", &(curr->Xloc));
		sscanf(row[7], "%i", &(curr->Yloc));
		curr->next = NULL;
	}
	
	mysql_free_result(result);
	return head;
}

PictureElementStruct_t* queryPictureElements(MYSQL *con) {
	if(con == NULL) {
		return NULL;
	}
	PictureElementStruct_t* head = NULL;//{ 0, 0, 0, 0, NULL };

	if (mysql_query(con, "SELECT * FROM HomeScreen A LEFT OUTER JOIN PictureElement B ON A.TypeID = B.ID WHERE A.Type=1")) 
	{
		return NULL;
	}
	
	MYSQL_RES *result = mysql_store_result(con);
	
	if (result == NULL) 
	{
		return NULL;
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;
	PictureElementStruct_t* curr;
	while ((row = mysql_fetch_row(result))) 
	{ 
		if(head == NULL) {
			//printf("\nHead is null, first item in list\n");
			curr = (PictureElementStruct_t *) malloc(sizeof(PictureElementStruct_t));
			head = curr;
		}
		else {
			//printf("\nHead is not null\n");
			curr->next = (PictureElementStruct_t *) malloc(sizeof(PictureElementStruct_t));
			curr = curr->next;
		}
		curr->data = malloc(sizeof(char) * (strlen(row[4]) + 1));
		strcpy(curr->data, row[4]);
		sscanf(row[5], "%i", &(curr->Xloc));
		sscanf(row[6], "%i", &(curr->Yloc));
		sscanf(row[7], "%i", &(curr->Width));
		sscanf(row[8], "%i", &(curr->Length));
		curr->next = NULL;
	}
	
	mysql_free_result(result);
	return head;
}

ImageStruct_t* setupImageStruct(PictureElementStruct_t* pictElemsHead) {
	if(pictElemsHead == NULL) {
		return NULL;
	}
	ImageStruct_t* head = NULL;
	ImageStruct_t* curr;
	while(pictElemsHead != NULL) {
		if(head == NULL) {
			curr = (ImageStruct_t *) malloc(sizeof(ImageStruct_t));
			head = curr;
		}
		else {
			curr->next = (ImageStruct_t *) malloc(sizeof(ImageStruct_t));
			curr = curr->next;
		}
		curr->image = LoadImage("resources/TestPic.png");
		ImageFormat(&(curr->image), UNCOMPRESSED_R8G8B8A8);
		curr->texture = LoadTextureFromImage(curr->image);
		curr->Xloc = pictElemsHead->Xloc;
		curr->Yloc = pictElemsHead->Yloc;
		curr->Width = pictElemsHead->Width;
		curr->Length = pictElemsHead->Length;
		curr->next = NULL;
		pictElemsHead = pictElemsHead->next;
	}
	return head;
}

void cleanImageStruct(ImageStruct_t* toClean) {
	ImageStruct_t* curr = toClean;
	ImageStruct_t* next;
	while(curr != NULL) {
		UnloadTexture(curr->texture);
		UnloadImage(curr->image);
		next = curr->next;
		free(curr);
		curr = next;
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
  
	TextElementStruct_t *headText = queryTextElements(con);
	PictureElementStruct_t *headPicture = queryPictureElements(con);
	struct ImageStruct *headImage = setupImageStruct(headPicture);
	struct ImageStruct *currImage = headImage;
	
	bool updateScreen = false;
	
	disconnectDB(con);

	time_t now;
	time_t oldFileTime;

	time(&now);

	printf("Today is : %s", ctime(&now));
	char* msg = ctime(&now);

	Font fontBm = LoadFont("resources/pixantiqua.fnt");

	Font fontTtf = LoadFontEx("resources/pixantiqua.ttf", 32, 0, 250);

	bool useTtf = false;
	
	char* displayTextFilePath = "DisplayText.txt";
	char* displayTextContent = LoadText(displayTextFilePath);

	SetTargetFPS(60);			   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------
	// Main game loop
	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyDown(KEY_SPACE)) useTtf = true;
		else useTtf = false;
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

		ClearBackground(RAYWHITE);
		
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
		DrawText(displayTextContent, 20, 20, 20, LIGHTGRAY);
		
		//----------- Database Updates
		if(tm->tm_sec%5 == 0) {
			if(updateScreen) {
				MYSQL *con = connectDB();
				headText = queryTextElements(con);
				headPicture = queryPictureElements(con);
				disconnectDB(con);
				
				cleanImageStruct(headImage);
				headImage = NULL;
				headImage = setupImageStruct(headPicture);
				updateScreen = false;
			}
		}
		else {
			updateScreen = true;
		}
		//-----------
		
		//----------- Loading Structs
		TextElementStruct_t *currText = headText;
		while(currText != NULL) {
			DrawText(currText->data, currText->Xloc, currText->Yloc, 20, BLUE);
			currText = currText->next;
		}
		currImage = headImage;
		while(currImage != NULL) {
			DrawTexture(currImage->texture, currImage->Xloc, currImage->Yloc, WHITE);
			currImage = currImage->next;
		}
		//-----------

		if (!useTtf)
		{
			DrawTextEx(fontBm, textClock, (Vector2){ 20.0f, 100.0f }, fontBm.baseSize, 2, MAROON);
			DrawText("Using BMFont (Angelcode) imported", 20, GetScreenHeight() - 30, 20, GRAY);
		}
		else
		{
			DrawTextEx(fontTtf, textClock, (Vector2){ 20.0f, 100.0f }, fontTtf.baseSize, 2, LIME);
			DrawText("Using TTF font generated", 20, GetScreenHeight() - 30, 20, GRAY);
		}
		
		drawClock(tm, vclockcenter, hclockcenter, 60.0);
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
