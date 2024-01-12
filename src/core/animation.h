#pragma once

#include <stdint.h>
#include <raylib.h>
#include <unordered_map>

struct Animation{
    int currentSpriteIndex;
    int spriteStart, len;
    bool willLoop;
};

struct AnimationSheet{
    Texture2D texSpritesheet;
    int spriteWidth, spriteHeight;
    int nHorizontal, nVertical;

    int fps;
    float frameDelay;

    float accumulator;
    Animation *currentAnimation;

    const char *defaultAnimation;

    std::unordered_map<const char*, Animation> animations;

    AnimationSheet(){}
    AnimationSheet(const char * filePath, int w, int h){
        Image imgSpritesheet = LoadImage(filePath);
        texSpritesheet = LoadTextureFromImage(imgSpritesheet);
        
        spriteWidth = w;
        spriteHeight = h;

        nHorizontal = imgSpritesheet.width/spriteWidth;
        nVertical   = imgSpritesheet.height/spriteHeight;

        UnloadImage(imgSpritesheet);
    }

    void addAnimation(const char *name, int start, int len, bool willLoop = true){
        Animation anim = {
            0, 
            start, len,
            willLoop
        };
        animations.insert_or_assign(name, anim);
    }

    void setFPS(int animFPS){
        fps = animFPS;
        frameDelay = 1.0f/fps;
    }

    void setDefaultAnimation(const char *name){
        defaultAnimation = name;
    }

    bool playAnimation(const char *name, float deltaTime, Rectangle dest){
        bool isFinished = false;
        // new animation
        if (currentAnimation != &animations[name]){
            currentAnimation = &animations[name];
            currentAnimation->currentSpriteIndex = 0;
            accumulator = 0;
        }
        
        accumulator += deltaTime;
        while (accumulator >= frameDelay){
            accumulator -= frameDelay;
            currentAnimation->currentSpriteIndex++;
        }

        if (currentAnimation->currentSpriteIndex >= currentAnimation->len){
            if (!currentAnimation->willLoop){
                currentAnimation = &animations[defaultAnimation];
            }
            currentAnimation->currentSpriteIndex = 0;
            isFinished = true;
        }

        Rectangle src = {
            ((currentAnimation->currentSpriteIndex + currentAnimation->spriteStart) % nHorizontal) * spriteWidth,
            ((currentAnimation->currentSpriteIndex + currentAnimation->spriteStart) / nHorizontal) * spriteHeight,
            spriteWidth,
            spriteHeight
        };

        DrawTexturePro(texSpritesheet, 
                        src, dest, 
                        {0,0}, 0, WHITE
                    );
        return isFinished;
    }
};




