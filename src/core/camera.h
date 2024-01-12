#pragma once

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

struct FollowCamera{
    Rectangle screen;
    Rectangle bufferZone;
    float zoom;
    Rectangle *follow;

    FollowCamera(){}
    FollowCamera(Rectangle *followSprite, int w, int h){
        follow = followSprite;
        screen.width = w; 
        screen.height = h;

        screen.x = (follow->x + follow->width * 0.5) - 0.5*w; 
        screen.y = (follow->y + follow->height * 0.5) - 0.5*h; 
    }

    void update(){
        screen.x += ((follow->x + follow->width * 0.5) - (screen.x + screen.width * 0.5f));
        screen.y += ((follow->y + follow->height * 0.5) - (screen.y + screen.height * 0.5f));
        printf("%f %f\n", screen.x, screen.y);
    }

    Rectangle toScreenSpace(Rectangle worldSpace){
        return Rectangle{
            worldSpace.x - screen.x,
            worldSpace.y - screen.y,
            worldSpace.width, 
            worldSpace.height
        };
    }


};

