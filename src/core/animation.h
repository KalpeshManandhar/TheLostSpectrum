#pragma once

#include <stdint.h>
#include <raylib.h>
#include <unordered_map>

struct Animation{
    int currentSpriteIndex;
    int spriteStart, len;
    bool willLoop;
};

static const uint32_t MOD_ADLER = 65521;

static uint32_t adler32(unsigned char *data, size_t len) 
/* 
    where data is the location of the data in physical memory and 
    len is the length of the data in bytes 
*/
{
    uint32_t a = 1, b = 0;
    size_t index;
    
    // Process each byte of the data in order
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    
    return (b << 16) | a;
}



struct AnimationSheet{
    Texture2D texSpritesheet;
    int spriteWidth, spriteHeight;
    int nHorizontal, nVertical;

    int fps;
    float frameDelay;

    float accumulator = 0;
    uint32_t currentAnimationHash;

    char defaultAnimation[10];
    uint32_t defaultAnimationHash;

    std::unordered_map<uint32_t, Animation> animations;

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

        uint32_t hash = adler32((unsigned char *)name, strlen(name));

        animations.insert_or_assign(hash, anim);
    }

    void setFPS(int animFPS){
        fps = animFPS;
        frameDelay = 1.0f/fps;
    }

    void setDefaultAnimation(const char *name){
        strcpy(defaultAnimation, name);
        defaultAnimationHash = adler32((unsigned char *)name, strlen(name));
    }

    bool playAnimation(const char *name, float deltaTime, Rectangle dest, int direction = 1){
        bool isFinished = false;
        uint32_t hash = adler32((unsigned char *)name, strlen(name));

        Animation* currentAnimation = &animations[currentAnimationHash];
        // new animation
        if (currentAnimation != &animations[hash]){
            currentAnimation = &animations[hash];
            currentAnimationHash = hash;
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
                currentAnimation = &animations[defaultAnimationHash];
                currentAnimationHash = defaultAnimationHash;
            }
            currentAnimation->currentSpriteIndex = 0;
            isFinished = true;
        }

        if (direction == 1) {
            Rectangle src = {
                ((currentAnimation->currentSpriteIndex + currentAnimation->spriteStart) % nHorizontal) * spriteWidth,
                ((currentAnimation->currentSpriteIndex + currentAnimation->spriteStart) / nHorizontal) * spriteHeight,
                spriteWidth,
                spriteHeight
            };

            DrawTexturePro(texSpritesheet,
                src, dest,
                { 0,0 }, 0, WHITE
            );
        }
        else {
            Rectangle src = {
                ((currentAnimation->currentSpriteIndex + currentAnimation->spriteStart) % nHorizontal) * spriteWidth,
                ((currentAnimation->currentSpriteIndex + currentAnimation->spriteStart) / nHorizontal) * spriteHeight,
                -spriteWidth,
                spriteHeight
            };

            DrawTexturePro(texSpritesheet,
                src, dest,
                { 0,0 }, 0, WHITE
            );
        }


        return isFinished;
    }
};




