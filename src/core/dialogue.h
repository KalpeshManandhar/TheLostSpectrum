#pragma once
#include <raylib.h>
#include <string.h>

struct DialogueArray{
    const char *text[];
};





struct DialogueBox{
    Texture2D picture;
    Rectangle characterRect;

    Rectangle dialogueBoxRect;
    Rectangle dialogueRect;

    static Font font;

    const float PADDING = 15;
    const float LINE_SPACING = 10;
    const float CHAR_SPACING = 0;


    DialogueBox(int windowW, int windowH){
        dialogueBoxRect = {PADDING, PADDING, windowW - 2 * PADDING, 256 + PADDING};
        characterRect = {PADDING, PADDING, 256,256};
        dialogueRect = {256 + PADDING, PADDING, windowW - 4*PADDING - 256, 256 + PADDING};
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


    void renderDialogue(const char *text, float deltaTime, float fontSize=32){
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

    void next(){

    }


};

Font DialogueBox::font = GetFontDefault();