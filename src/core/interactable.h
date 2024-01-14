#pragma once

#include "dialogue.h"
#include "geometry.h"

struct Interactable{
    Rectangle spriteRect;
    AnimationSheet anim;
    Circle triggerRange;

    DialogueArray dialogues;

    Interactable(){}
    Interactable(const char *spritePath, int w, int h){
        anim = AnimationSheet(spritePath,  w, h);

    }

    void animate(FollowCamera *c, float deltaTime){
        Rectangle r = c->toScreenSpace(spriteRect);
        
        anim.playAnimation(anim.defaultAnimation, deltaTime, r, 1);
    }
    
};


