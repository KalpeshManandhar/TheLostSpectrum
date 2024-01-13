#pragma once
#include <raylib.h>
#include <string.h>

#define DLG_ARRAY_SIZE 20
#define DEFAULT_FONT_SIZE 32

struct DialogueArray{
    char text[DLG_ARRAY_SIZE][60] = {0};
};





struct DialogueBox{
    Texture2D picture;
    Rectangle characterRect;

    Rectangle dialogueBoxRect;
    Rectangle dialogueRect;

    const float PADDING = 15;
    const float LINE_SPACING = 10;
    const float CHAR_SPACING = 0;

    int currentDlgIndex;
    DialogueArray *dlg;

    DialogueBox(int windowW = 1280, int windowH = 720){
        dialogueBoxRect = {PADDING, PADDING, windowW - 2 * PADDING, windowH * 0.3f};
        characterRect = {
            dialogueBoxRect.x + PADDING, dialogueBoxRect.y + dialogueBoxRect.height *0.1f, 
            dialogueBoxRect.height *0.8f, dialogueBoxRect.height *0.8f
        };
        dialogueRect = {
            characterRect.x + characterRect.width + 2*PADDING, characterRect.y + PADDING, 
            dialogueBoxRect.width - characterRect.width - 2 * PADDING, dialogueBoxRect.height - 2 * PADDING
        };
    }

    int getNextWordLength(const char *text){
        int wordlen = 0;
        while (text[wordlen] != 0 && text[wordlen] != ' ' && text[wordlen] != '.' && text[wordlen] != ','){
            wordlen++;
        }
        return (wordlen+1);
    }

    void renderCharacter(char ch, Vector2 pos, float fontSize){
        char cstr[2] = {ch, 0};
        DrawText(cstr, pos.x, pos.y, fontSize, WHITE);
    }


    void renderDialogue(const char *text, float deltaTime, float fontSize=DEFAULT_FONT_SIZE){
        DrawRectangleLinesEx(characterRect, 6, Color{64,64,64,128});
        DrawRectangleRec(dialogueBoxRect, Color{64,64,64,128});
        
        int index = 0;
        int rowNo = 0, column = 0; 
        int columnsInARow = (dialogueRect.width - PADDING * 2)/fontSize;
        int len = strlen(text);
        
        while (index < len){
            int nextWordLen = getNextWordLength(&text[index]);
            if (column + nextWordLen > columnsInARow){
                rowNo++;
                column = 0;
            }

            for (int i=0; i<nextWordLen; i++){
                Vector2 currentPos = {
                    dialogueRect.x + 2 * PADDING + (column + i) * (fontSize + CHAR_SPACING), 
                    dialogueRect.y + 2.5 * PADDING + rowNo * (fontSize + LINE_SPACING)
                };

                renderCharacter(text[index + i], currentPos, fontSize);
            }
            column += nextWordLen;
            index += nextWordLen;
        }


    }

    void setNewDialogueArray(DialogueArray * dialogues){
        dlg = dialogues;
        currentDlgIndex = 0;
    }

    bool nextDlg(){
        currentDlgIndex++;
        if (currentDlgIndex < DLG_ARRAY_SIZE && dlg->text[currentDlgIndex][0] != 0){
            return true;
        }
        
        currentDlgIndex = 0;
        return false;
    }


    void show(float deltaTime, float fontSize = DEFAULT_FONT_SIZE){
        renderDialogue(dlg->text[currentDlgIndex], deltaTime);
    }
};

