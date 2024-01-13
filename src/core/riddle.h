#pragma once
#include<raylib.h>
#include "dialogue.h"
#include <iostream>

class riddle
{
	const float PADDING = 10;
	const int riddleDialogueSize = 3;
	const int riddleTextSize = 4;
	Rectangle characterRect;
	bool winDisplay,riddleDisplay,empty = false;	

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
		//if (winDisplay==false)
		//{
			std::cout << "Inside" << std::endl;
			for (int i = 0; i < 2; i++)			
				DrawText(TextFormat(riddleDialogue[i]), dialogueBoxRect.x + PADDING, dialogueBoxRect.y + i * 20 + PADDING, 20, WHITE);
		//}
		//winDisplay = true;		
		/*if (!riddleDisplay)
		{
			for (int i = 0; i < riddleTextSize; i++)
				DrawText(TextFormat(riddleText[i]), dialogueBoxRect.x + PADDING, dialogueBoxRect.y + i * 20 + PADDING, 20, WHITE);
			
			
		}*/
		riddleDisplay = true;
		winDisplay = true;
		
		
			//DrawText(TextFormat(riddleDialogue[i]),dialogueBoxRect.x+PADDING,dialogueBoxRect.y+PADDING,20,WHITE);
			//DrawText(riddleDialogue[0], dialogueBoxRect.x + PADDING, dialogueBoxRect.y + PADDING, 20, WHITE);
	}
	bool isEmpty()
	{
		if(riddleDisplay && winDisplay)
			return !empty;
	}


};
