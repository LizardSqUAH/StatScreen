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
//#include "mysql.h"
//#include "my_global.h"
//-----------------

//string readTextFile() {
//	return "";
//}


int drawClock(struct tm *tm, float vcc, float hcc, float radius) {
	float hclocks = radius * sin((tm->tm_sec / 60.0) * 2.0 * 3.14159265);
	float vclocks = radius * cos((tm->tm_sec / 60.0) * 2.0 * 3.14159265);
	float hclockm = radius * sin((tm->tm_min / 60.0) * 2.0 * 3.14159265);
	float vclockm = radius * cos((tm->tm_min / 60.0) * 2.0 * 3.14159265);
	float hclockh = radius * sin((tm->tm_hour / 12.0) * 2.0 * 3.14159265);
	float vclockh = radius * cos((tm->tm_hour / 12.0) * 2.0 * 3.14159265);
	/*printf ("%04d-%02d-%02d %02d:%02d:%02d\nhclocks: %f\tvclocks: %f\n",
	 tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
	 tm->tm_hour, tm->tm_min, tm->tm_sec, hclocks, vclocks);*/
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
    long sqlversion = mysql_get_client_version();
    printf("Version %ld \n", sqlversion);
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    struct tm *tm;
    int vclockcenter = 100;
    int hclockcenter = 700;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - bmfont and ttf sprite fonts loading");

    // time_t is arithmetic time type
    time_t now;
    time_t oldFileTime;

    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);

    // Convert to local time format and print to stdout
    printf("Today is : %s", ctime(&now));
    char* msg = ctime(&now);

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    // BMFont (AngelCode) : Font data and image atlas have been generated using external program
    Font fontBm = LoadFont("resources/pixantiqua.fnt");

    // TTF font : Font data and atlas are generated directly from TTF
    // NOTE: We define a font base size of 32 pixels tall and up-to 250 characters
    Font fontTtf = LoadFontEx("resources/pixantiqua.ttf", 32, 0, 250);

    bool useTtf = false;
    
    char* displayTextFilePath = "DisplayText.txt";
    char* displayTextContent = LoadText(displayTextFilePath);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
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
    UnloadFont(fontBm);     // AngelCode Font unloading
    UnloadFont(fontTtf);    // TTF Font unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
