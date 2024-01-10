#include<raylib.h>

class splashScreen {
private:
	int splashDuration;
	Vector2 titlePosition;
	char* text;

public:
	const double startTime = GetTime();

	splashScreen(char* t, int screenWidth = 1280, int screenHeight = 720) {
		splashDuration = 3;
		text = t;
		titlePosition = { (float(screenWidth) - MeasureText(text, 50)) / 2,float(screenHeight) / 2 - 50 };
	}

	void displaySplashScreen(Color textColour, Color bgColour) {
		while ((GetTime() - startTime) < splashDuration) {
			BeginDrawing();
			ClearBackground(bgColour);
			DrawText(text, static_cast<int>(titlePosition.x), static_cast<int>(titlePosition.y), 50, textColour);

			EndDrawing();
		}
	}

};