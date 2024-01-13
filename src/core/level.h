#pragma once

#include "camera.h"
#include "lexer.h"

#include <stdio.h>
#include <string>
#include <raylib.h>

#define Max(a,b) ((a)>(b)? (a):(b))
#define Min(a,b) ((a)<(b)? (a):(b))

struct LevelMap{
    // no of tiles in the level map
    int w, h;

    int tileW, tileH;
    Texture2D texTilemap;
    // no of tiles in the tilemap
    int nTileHor, nTileVert;

    int destTileW, destTileH;

    int *base; 
    int *overlay; 
    int *collisionMap;

    Vector2 playerSpawn;

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
        
        Image tilesImg = LoadImage("./assets/levelmaps/tilemap.png");
        texTilemap = LoadTextureFromImage(tilesImg);
        UnloadImage(tilesImg);

        std::string dir(levelDir);
        readInfo((dir + "/info.txt").c_str());

        base = readCSV((dir + "/base.csv").c_str());
        overlay = readCSV((dir + "/overlay.csv").c_str());
        collisionMap = readCSV((dir + "/collision.csv").c_str());
    }

    ~LevelMap(){
        if (base) delete[] base;
        if (overlay) delete[] overlay;
        if (collisionMap) delete[] collisionMap;
    }



    void displayBase(FollowCamera *c){
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

                DrawTexturePro(texTilemap, src, dest, {0,0}, 0, WHITE);
            }   
        }

    }
    void displayOverlay(FollowCamera *c){
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

                DrawTexturePro(texTilemap, src, dest, {0,0}, 0, WHITE);
            }   
        }

    }
};
