//#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"

int main(void)
{
    //system("nmap -v -sn 10.252.156.1/22"); 

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    struct tm *tm;
    float vclocks = 0;
    float hclocks = 0;
    float vclockm = 0;
    float hclockm = 0;
    float vclockh = 0;
    float hclockh = 0;
    int vclockcenter = 300;
    int hclockcenter = 600;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - bmfont and ttf sprite fonts loading");

    // time_t is arithmetic time type
    time_t now;

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
        char dangerous[strlento+strlenmsg];
        for(int i = 0; i < strlento; i++) {
                dangerous[i] = toover[i];
        }
        dangerous[strlento] = '\0';
        for(int i = 0; i < strlenmsg; i++) {
                dangerous[i+strlento] = msg[i];
        }
        dangerous[strlenmsg+strlento] = '\0';
        //char* test = ctime(&now);
        //strcpy(msg, test);
        //printf("%s", test);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Hold SPACE to use TTF generated font", 20, 20, 20, LIGHTGRAY);

            if (!useTtf)
            {
                DrawTextEx(fontBm, dangerous, (Vector2){ 20.0f, 100.0f }, fontBm.baseSize, 2, MAROON);
                DrawText("Using BMFont (Angelcode) imported", 20, GetScreenHeight() - 30, 20, GRAY);
            }
            else
            {
                DrawTextEx(fontTtf, dangerous, (Vector2){ 20.0f, 100.0f }, fontTtf.baseSize, 2, LIME);
                DrawText("Using TTF font generated", 20, GetScreenHeight() - 30, 20, GRAY);
            }

	    hclocks = 100 * sin((tm->tm_sec / 60.0) * 2.0 * 3.14159265);
	    vclocks = 100 * cos((tm->tm_sec / 60.0) * 2.0 * 3.14159265);
	    hclockm = 100 * sin((tm->tm_min / 60.0) * 2.0 * 3.14159265);
	    vclockm = 100 * cos((tm->tm_min / 60.0) * 2.0 * 3.14159265);
	    hclockh = 100 * sin((tm->tm_hour / 12.0) * 2.0 * 3.14159265);
	    vclockh = 100 * cos((tm->tm_hour / 12.0) * 2.0 * 3.14159265);
	    printf ("%04d-%02d-%02d %02d:%02d:%02d\nhclocks: %f\tvclocks: %f\n",
	         tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
	         tm->tm_hour, tm->tm_min, tm->tm_sec, hclocks, vclocks);
	    
	    for(int i = 0; i < 60; i++) {
		if(i%15 == 0) {
		     DrawLine(hclockcenter + 90 * sin((i / 60.0) * 2.0 * 3.14159265), vclockcenter + -90 * cos((i / 60.0) * 2.0 * 3.14159265), hclockcenter + 100 * sin((i / 60.0) * 2.0 * 3.14159265), vclockcenter + -100 * cos((i / 60.0) * 2.0 * 3.14159265), BLACK);
		}
		else if(i%5 == 0) {
		     DrawLine(hclockcenter + 95 * sin((i / 60.0) * 2.0 * 3.14159265), vclockcenter + -95 * cos((i / 60.0) * 2.0 * 3.14159265), hclockcenter + 100 * sin((i / 60.0) * 2.0 * 3.14159265), vclockcenter + -100 * cos((i / 60.0) * 2.0 * 3.14159265), BLACK);
		}
		else {
		     DrawPixel(hclockcenter + 100 * sin((i / 60.0) * 2.0 * 3.14159265), vclockcenter + -100 * cos((i / 60.0) * 2.0 * 3.14159265), BLACK);
		}
		//For all i%5 == 0, dont want to skip 15s
		if(i%5 == 0) {
		     char itostr[2];
		     if(i == 0) {
		     	itostr[0] = '1';
		     	itostr[1] = '2';
		     }
		     else {
			sprintf(itostr, "%d", i/5);
		     }
		     DrawText(itostr, hclockcenter - 5 + 120 * sin((i / 60.0) * 2.0 * 3.14159265), vclockcenter - 10 + -120 * cos((i / 60.0) * 2.0 * 3.14159265), 20, BLUE);
		}
	    }
            DrawLine(hclockcenter, vclockcenter, hclockcenter + hclocks, vclockcenter - vclocks, RED);
            DrawLine(hclockcenter, vclockcenter, hclockcenter + hclockm * 0.8, vclockcenter - vclockm * 0.8, BLUE);
            DrawLine(hclockcenter, vclockcenter, hclockcenter + hclockh * 0.5, vclockcenter - vclockh * 0.5, BLACK);

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
