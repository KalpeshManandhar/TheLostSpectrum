#pragma once
#include<raylib.h>
#include "dialogue.h"
#include <iostream>



class inputBox
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	char name[10 + 1] = "\0";
	int letterCount = 0;

	Rectangle textBox = { screenWidth / 2.0f - 100, 180, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

public:
	void drawInputBox()
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		// Get char pressed (unicode character) on the queue
		int key = GetCharPressed();

		// Check if more characters have been pressed on the same frame
		while (key > 0)
		{
			// NOTE: Only allow keys in range [32..125]
			if ((key >= 32) && (key <= 125) && (letterCount < 10))
			{
				name[letterCount] = (char)key;
				name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
				letterCount++;
			}

			key = GetCharPressed();  // Check next character in the queue
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			letterCount--;
			if (letterCount < 0) letterCount = 0;
			name[letterCount] = '\0';
		}

		else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

		if (mouseOnText) framesCounter++;
		else framesCounter = 0;


		//DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

		DrawRectangleRec(textBox, LIGHTGRAY);
		if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
		else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 10), 315, 250, 20, DARKGRAY);

		if (mouseOnText)
		{
			if (letterCount < 10)
			{
				// Draw blinking underscore char
				if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
			}
			else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
		}
	}

};

class riddle
{
	const float PADDING = 10;
	const int riddleDialogueSize = 3;
	const int riddleTextSize = 4;
	Rectangle characterRect;
	
	inputBox box;
	
	int state=0;
	Rectangle dialogueBoxRect;
	Rectangle dialogueRect;
	char riddleDialogue[3][100] =
	{
		"Hey there, fearless adventurer!",
		"So, you've bested the boss and stumbled uponthe Chromalock, the bouncer of the rainbow realm.",
		"To crack its colorful code, think in rhymes"
	};
	char riddleText[4][100]=
	{
		"In realms unseen, our houses lay",
		"A device conceals us in a play",
		"Search everywhere- a key it holds",
		"Retrieve it to see the colors unfold"
	};

public:

	void riddleBox(int windowW = 1280, int windowH = 720)
	{
		dialogueBoxRect = { PADDING, windowH * 0.7f - PADDING, windowW - 2 * PADDING, windowH * 0.3f };
		DrawRectangleRec(dialogueBoxRect, Color{ 64,64,64,128 });
		std::cout << state << "\n";
		switch (state)
		{
		case 0:
			//std::cout << "Inside" << std::endl;
			for (int i = 0; i < riddleDialogueSize; i++)
				DrawText(TextFormat(riddleDialogue[i]), dialogueBoxRect.x + PADDING, dialogueBoxRect.y + i * 20 + PADDING, 20, WHITE);
			break;
		case 1:
			//std::cout << "Inside" << std::endl;
			for (int i = 0; i < riddleTextSize; i++)
				DrawText(TextFormat(riddleText[i]), dialogueBoxRect.x + PADDING, dialogueBoxRect.y + i * 20 + PADDING, 20, WHITE);
			break;
		case 2:
			box.drawInputBox();
			break;

		default:
			break;
		}
			
	}

	bool choose()
	{
		state=(state+1)%4;
		if (state == 3)
		{
			state = 0;
			return false;
		}
		return true;

		
	}


};

