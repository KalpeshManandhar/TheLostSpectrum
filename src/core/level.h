#pragma once

#include "camera.h"
#include "lexer.h"
#include "interactable.h"

#include <stdio.h>
#include <string>
#include <raylib.h>



struct LevelMap{
    // no of tiles in the level map
    int w, h;

    int tileW, tileH;
    Texture2D texTilemap;
    Texture2D texTilemapGrayScale;
    // no of tiles in the tilemap
    int nTileHor, nTileVert;
    Color mask;

    int destTileW, destTileH;

    int *base; 
    int *overlay; 
    int *collisionMap;

    Vector2 playerSpawn;
    Vector2 npcSpawn;
    Vector2 bossSlimeSpawn;

    Interactable interactable[10];

    void readInfo(const char *path){
        Lexer l;
        l.loadFile(path);

        w = l.skipAndParseInt();
        h = l.skipAndParseInt();
        tileW = l.skipAndParseInt();
        tileH = l.skipAndParseInt();
        nTileHor = l.skipAndParseInt();
        nTileVert = l.skipAndParseInt();
        playerSpawn.x = l.skipAndParseInt() * destTileW;
        playerSpawn.y = l.skipAndParseInt() * destTileH;
        npcSpawn.x = playerSpawn.x + 300;
        npcSpawn.y = playerSpawn.y;
    }

    int* readCSV(const char *path){
        Lexer l;
        l.loadFile(path);

        int *r = new int[w*h];
        for (int i=0; i< w*h; i++){
            r[i] = l.skipAndParseInt();
        }
        return r;
    }


    LevelMap(){}
    LevelMap(const char *levelDir, const char *tilemapPath, Vector2 destTileDim){
        destTileW = destTileDim.x;
        destTileH = destTileDim.y;
        
        Image imgTilemap = LoadImage(tilemapPath);
        texTilemap = LoadTextureFromImage(imgTilemap);
        ImageColorGrayscale(&imgTilemap);
        texTilemapGrayScale = LoadTextureFromImage(imgTilemap);
        UnloadImage(imgTilemap);

        std::string dir(levelDir);
        readInfo((dir + "/info.txt").c_str());

        base = readCSV((dir + "/base.csv").c_str());
        overlay = readCSV((dir + "/overlay.csv").c_str());
        collisionMap = readCSV((dir + "/collision.csv").c_str());
        mask = WHITE;
    }

    void setColorMask(Color colorMask){
        mask = colorMask;
    }

    ~LevelMap(){
        if (base) delete[] base;
        if (overlay) delete[] overlay;
        if (collisionMap) delete[] collisionMap;
    }

    void displayTile(Rectangle src, Rectangle dest, int shardsCollected){
        switch (shardsCollected){
        case 0:
            DrawTexturePro(texTilemapGrayScale, src, dest, {0,0}, 0, {255,255,255,255});
            break;
        case 1:
            DrawTexturePro(texTilemap, src, dest, {0,0}, 0, {165,0,0,255});
            break;
        case 2:
            DrawTexturePro(texTilemap, src, dest, {0,0}, 0, {165,135,0,255});
            break;
        case 3:
            DrawTexturePro(texTilemap, src, dest, {0,0}, 0, WHITE);
            break;
        
        default:
            break;
        }
    }

    void displayBase(FollowCamera *c, int shardsCollected){
        int startTileX = Max((c->screen.x)/destTileW,0);
        int startTileY = Max((c->screen.y)/destTileH,0);

        int endTileX =  Min((c->screen.x + c->screen.width)/destTileW + 1, w - 1);
        int endTileY =  Min((c->screen.y + c->screen.height)/destTileH + 1, h - 1);

        for (int i=startTileY; i<= endTileY;  i++){
            for (int j=startTileX; j<= endTileX;  j++){
                int tileIndex = base[i*w + j];
                if (tileIndex == -1)
                    continue;
                int offsetX = tileIndex%nTileHor;
                int offsetY = tileIndex/nTileHor;
                
                Rectangle src = {
                    offsetX * tileW, offsetY * tileH,
                    tileW, tileH
                };

                Rectangle dest = {
                    j * destTileW, i * destTileH,
                    destTileW, destTileH 
                };
                dest = c->toScreenSpace(dest);
                displayTile(src, dest, shardsCollected);
            }   
        }

    }
    void displayOverlay(FollowCamera *c, int shardsCollected){
        int startTileX = Max((c->screen.x)/destTileW,0);
        int startTileY = Max((c->screen.y)/destTileH,0);

        int endTileX =  Min((c->screen.x + c->screen.width)/destTileW + 1, w - 1);
        int endTileY =  Min((c->screen.y + c->screen.height)/destTileH + 1, h - 1);

        for (int i=startTileY; i<= endTileY;  i++){
            for (int j=startTileX; j<= endTileX;  j++){
                int tileIndex = overlay[i*w + j];
                if (tileIndex == -1)
                    continue;

                int offsetX = tileIndex%nTileHor;
                int offsetY = tileIndex/nTileHor;
                
                Rectangle src = {
                    offsetX * tileW, offsetY * tileH,
                    tileW, tileH
                };

                Rectangle dest = {
                    j * destTileW, i * destTileH,
                    destTileW, destTileH 
                };
                dest = c->toScreenSpace(dest);

                displayTile(src, dest, shardsCollected);

            }   
        }

    }
};
