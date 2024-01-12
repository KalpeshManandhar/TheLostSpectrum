#include<raylib.h>
#include <string>
#include "gifAnim/gifAnim.h"

class splashScreen {
private:
	int splashDuration;
	int fontsize;
	Vector2 titlePosition;
	char* text;
	double elapsedTime;
	int lettersToShow;

public:
	const double startTime = GetTime();
	splashScreen(char* t, int fs = 50, int screenWidth = 1280, int screenHeight = 720, int duration = 7) {
		splashDuration = duration;
		text = t;
		fontsize = fs;
		elapsedTime = 0.0;
		titlePosition = { (float(screenWidth) - MeasureText(text, fontsize)) / 2,float(screenHeight) / 2 - fontsize };
	}

	void displaySplashScreen(Color textColour, Color bgColour, const char* gifPath,int gifSingleWidth, int gifSingleHeight, int gifStart, int gifTotal) {
		auto oceanData = gifInit(gifPath, gifSingleWidth, gifSingleHeight, gifStart, gifTotal);
		
		while ((GetTime() - startTime) < splashDuration) {
			BeginDrawing();
			ClearBackground(bgColour);

			gifLoop(&oceanData, GetFrameTime());
			
			DrawText(text, static_cast<int>(titlePosition.x), static_cast<int>(titlePosition.y), fontsize, textColour);

			EndDrawing();
		}
	}

	void displayConvo(Color textColour, Color bgColour, const char* imgPath) {
		elapsedTime = (GetTime() - startTime);
		Image image = LoadImage(imgPath);
		Texture2D convoTexture = LoadTextureFromImage(image);

		UnloadImage(image);
		while (1) {
			BeginDrawing();
			ClearBackground(bgColour);

			DrawTexture(convoTexture, 0, 0, WHITE);

			// Draw the text letter by letter
			DrawText(text, static_cast<int>(titlePosition.x), static_cast<int>(titlePosition.y), fontsize, textColour);
			EndDrawing();

			if (IsKeyPressed(KEY_ENTER))
				break;
	}
			UnloadTexture(convoTexture);
	}
};