#include<raylib.h>
#include "gifAnim/gifAnim.h"

class splashScreen {
private:
	int splashDuration;
	int animDuration;
	Vector2 titlePosition;
	char* text;

public:
	const double startTime = GetTime();
	splashScreen(char* t, int screenWidth = 1280, int screenHeight = 720, int duration = 7) {
		splashDuration = duration;
		text = t;
		titlePosition = { (float(screenWidth) - MeasureText(text, 50)) / 2,float(screenHeight) / 2 - 50 };
	}

	void displaySplashScreen(Color textColour, Color bgColour, const char* gifPath,int gifSingleWidth, int gifSingleHeight, int gifStart, int gifTotal) {
		auto oceanData = gifInit(gifPath, gifSingleWidth, gifSingleHeight, gifStart, gifTotal);
		
		while ((GetTime() - startTime) < splashDuration) {
			BeginDrawing();
			ClearBackground(bgColour);

			gifLoop(&oceanData, GetFrameTime());
			
			DrawText(text, static_cast<int>(titlePosition.x), static_cast<int>(titlePosition.y), 50, textColour);

			EndDrawing();
		}
	}

	void diaplayGif() {
		while ((GetTime() - startTime) < splashDuration) {
			BeginDrawing();
			ClearBackground(BLACK);


			

			DrawText(text, static_cast<int>(titlePosition.x), static_cast<int>(titlePosition.y), 50, WHITE);

			EndDrawing();
		}
	}
};