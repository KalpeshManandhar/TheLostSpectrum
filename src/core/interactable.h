#pragma once

#include "dialogue.h"
#include "geometry.h"

struct Interactable{
    Rectangle spriteRect;
    Texture2D sprite;
    Circle triggerRange;

    DialogueArray dialogues;

    Interactable(const char *filePath){
        
    }

    void animate(){

    }

    void onInteractionDisplay(DialogueBox *db, float deltaTime){
        // db->renderDialogue(dialogues.text[currentDlgIndex], deltaTime);
    }

    
};


