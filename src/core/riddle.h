#pragma once
#include<raylib.h>
#include "dialogue.h"
#include <iostream>
#include <fstream>



class inputBox
{
	bool onceTrue = false;
	bool isWrong = false;
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();	

	char answer[10 + 1] = "\0";
	int letterCount = 0;

	Rectangle textBox = { screenWidth / 2.0f - 100, 180, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

public:
	bool drawInputBox()
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
				answer[letterCount] = (char)key;
				answer[letterCount + 1] = '\0'; // Adding null terminator at the end of the string.
				letterCount++;
			}

			key = GetCharPressed();  // Check next character in the queue
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			letterCount--;
			if (letterCount < 0) letterCount = 0;
			answer[letterCount] = '\0';
			isWrong = false;
			

		}

		else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

		if (mouseOnText) framesCounter++;
		else framesCounter = 0;



		DrawRectangleRec(textBox, LIGHTGRAY);
		if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
		else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		DrawText(answer, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		DrawText(TextFormat("INPUT: %i/%i", letterCount, 10), 315, 250, 20, DARKGRAY);
		if(isWrong)
			DrawText("Wrong! Please try again", textBox.x - 100, textBox.y + 100, 40, RED);

		if (mouseOnText)
		{
			if (letterCount < 10)
			{
				// Draw blinking underscore char
				if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(answer, 40), (int)textBox.y + 12, 40, MAROON);
			}
			else DrawText("Press BACKSPACE to delete", 230, 300, 20, GRAY);
		}
		if (IsKeyPressed(KEY_ENTER))
		{			
			std::cout << answer << '\n';
			if (strcmp(answer, "rainbow") == 0)
			{
				isWrong = false;
				onceTrue = true;
				return true;
			}
				
			else
			{
				isWrong = true;
				
				return false;
			}
				
		}
		if (onceTrue)
			return true;
	}

};

class riddle
{
	const float PADDING = 10;
	const int riddleDialogueSize = 3;
	const int riddleTextSize = 4;
	Rectangle characterRect;

	std::fstream FILE;
	std::string filename = "test.riddle";
	
	inputBox box;
	bool file=true;
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
	riddle()
	{
		if (file)
		{
			FILE.open(filename, std::ios::out);
			if (!FILE)
				std::cout << "ERROR";
			else
			{
				std::cout << "YAY";
				FILE << "rainbow";

			}
			FILE.close();
			file = false;

		}
	}
	~riddle()
	{
		int res=remove(filename.c_str());
	}

	void riddleBox(int windowW = 1280, int windowH = 720)
	{
		
		std::cout << state << "\n";
		
		switch (state)
		{
		case 0:
			dialogueBoxRect = { PADDING, windowH * 0.7f - PADDING, windowW - 2 * PADDING, windowH * 0.3f };
			DrawRectangleRec(dialogueBoxRect, Color{ 64,64,64,128 });
			//std::cout << "Inside" << std::endl;
			for (int i = 0; i < riddleDialogueSize; i++)
				DrawText(TextFormat(riddleDialogue[i]), dialogueBoxRect.x + PADDING, dialogueBoxRect.y + i * 20 + PADDING, 20, WHITE);
			break;
		case 1:
			dialogueBoxRect = { PADDING, windowH * 0.7f - PADDING, windowW - 2 * PADDING, windowH * 0.3f };
			DrawRectangleRec(dialogueBoxRect, Color{ 64,64,64,128 });
			//std::cout << "Inside" << std::endl;
			for (int i = 0; i < riddleTextSize; i++)
				DrawText(TextFormat(riddleText[i]), dialogueBoxRect.x + PADDING, dialogueBoxRect.y + i * 20 + PADDING, 20, WHITE);
			break;
		case 2:
		{
			
			bool check = box.drawInputBox();
			if (check)
			{
				dialogueBoxRect = { PADDING*4, windowH * 0.35f - PADDING, windowW - 6 * PADDING, windowH * 0.1f };
				DrawRectangleRec(dialogueBoxRect, Color{ 64,64,64,128 });
				DrawText(TextFormat("CONGRATULATIONS!!!YOU HAVE RESTORED THE COLORS"), dialogueBoxRect.x + PADDING, dialogueBoxRect.y + PADDING, 40, WHITE);
				if (IsKeyPressed(KEY_B))
					state = 10;

			}

			break;

		}
			

		default:
			
			break;
		}
			
	}

	bool choose()
	{
		if (state == 10)
			return false;
		state=(state+1)%4;
		if (state == 3)
		{
			state = 10;
			return false;
		}
		return true;

		
	}


};

