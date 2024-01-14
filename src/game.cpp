#include "game.h"
#include <iostream>

#include "player.cpp"
#include "tests/tests.h"
#include "core/collision.h"
#include <assert.h>

#include "info.h"

Game::Game(unsigned int width, unsigned int height): db(width, height){
    stateStack.push_back(GameState::GAME_ACTIVE);
    Width = width;
    Height = height;
}   


Game::~Game() {

    UnloadTexture(testData->background);
}


void Game::Init() {
    testData = testInit();
    level1 = loadLevel(level1INFO.levelDir);
    currentLevel = level1;

    filterShader = LoadShader(0, "./src/shaders/rgb.fs");

    loadInteractable(level1INFO.interactFiles[0]);
    loadInteractable(level1INFO.interactFiles[1]);


    memset(slimehits, 0, 3 * sizeof(int));
}


DialogueArray d = {
    "I am mad scientist.",
    "It's so cool",
    "Sonuvabitch"
};

void Game::ProcessInput(float dt) {
    switch (stateStack.back())
    {
    case GAME_DIALOGUE:
        if (IsKeyPressed(KEY_Q)){
            if (!db.nextDlg()){
                stateStack.pop_back();
            }
        }
        break;
    case GAME_RIDDLE:
        if (IsKeyPressed(KEY_R))
        {
            if (!r.choose())
            {
                stateStack.pop_back();
            }
                
        }
        break;        
       
    case GAME_ACTIVE:
        if (IsKeyPressed(KEY_Q)){
            // stateStack.push_back(GameState::GAME_DIALOGUE);
            // db.setNewDialogueArray(&d);
            if (checkInteractions()){
                stateStack.push_back(GameState::GAME_DIALOGUE);
            }
            //break;
        }
        if (IsKeyPressed(KEY_R)) {
            stateStack.push_back(GameState::GAME_RIDDLE);
            //db.setNewDialogueArray(&d);
            //break;
        }
        if (IsKeyPressed(KEY_KP_1)){
            shardsCollected = (shardsCollected + 1)%4;
        }
        if (IsKeyPressed(KEY_X)){
            level2 = loadLevel(level2INFO.levelDir);
            interactables.clear();
            loadInteractable(level2INFO.interactFiles[0]);

            currentLevel = level2;
            Vector2 toNewPos = {
                currentLevel->playerSpawn.x - testData->player.sprite.x,
                (currentLevel->playerSpawn.y - testData->player.sprite.y)/ZY_FACTOR,
            };
            testData->player.updatePos(toNewPos);
        }


        // testData->player.resolveChanges();
        testLoop(testData, dt);
        
        break;
    
    default:
        break;
    }

}
Rectangle tile;

void Game::Update( float dt)
{
    for (auto gs : stateStack) {

        switch (gs)
        {
        case GAME_ACTIVE:
            testData->c.update();


            currentLevel->displayBase(&testData->c, shardsCollected);
            
            for (auto &i : interactables){
                i.animate(&testData->c, dt);
            }
            if (currentLevel != level2){
                displaySlime(testData, dt);
            }


            testData->player.animate(&testData->c, dt);

            currentLevel->displayOverlay(&testData->c, shardsCollected);
            DrawRectangleLinesEx(tile, 12, WHITE);

            if (circleCircleCollisionCheck(testData->slime[0].hurtbox, testData->player.hurtbox))
            {
                const double s0time = GetTime();
                if (testData->player.isAttacking && testData->slime[0].isActive) 
                {
                    testData->slime[0].state = testData->slime[0].SLIME_DIE;
                }
            }
            if (circleCircleCollisionCheck(testData->slime[1].hurtbox, testData->player.hurtbox)) 
            {

                if (testData->player.isAttacking && testData->slime[1].isActive) 
                {
                    testData->slime[1].state = testData->slime[1].SLIME_DIE;
                }
            }
            if (circleCircleCollisionCheck(testData->slime[2].hurtbox, testData->player.hurtbox))
            {

                if (testData->player.isAttacking && testData->slime[2].isActive) 
                {
                    testData->slime[2].state = testData->slime[2].SLIME_DIE;
                }
            }

            updateSlimeBoss(testData->slime[3], dt,testData->player);
            

            break;

        case GAME_DIALOGUE:
            db.show(dt);
            break;
        case GAME_RIDDLE:
            r.riddleBox();
            break;

        default:
            break;
        }
    }
}
 
    //Player.draw({0,0});
    //Player.movementCheck();

    //DrawText("INITIAL CONVERSATION STARTS", static_cast<int>((Width / 2) - 250), static_cast<int>(Height / 2), 50, WHITE);
    


void Game::DoCollitions() {


}

void Game::ResetLevel()
{
}

void Game::ResetPlayer()
{
}



void Game::fixedLoop(float dt)
{
    testFixedLoop(testData, dt);
    
    Vector2 worldPos = {
        testData->player.sprite.x + 0.5*testData->player.sprite.width,
        testData->player.sprite.y + 0.5*testData->player.sprite.height
    };
    Vector2 tilePos = {worldPos.x/currentLevel->destTileW, worldPos.y/currentLevel->destTileH};

    int startTileX = Max(0, tilePos.x - 4);
    int startTileY = Max(0, tilePos.y - 4);
    int endTileX = Min(currentLevel->w, tilePos.x + 4);
    int endTileY = Min(currentLevel->h, tilePos.y + 4);

    for (int j = startTileY; j<endTileY; j++){
        for (int i = startTileX; i<endTileX; i++){
            if (currentLevel->collisionMap[j * currentLevel->w + i] == -1){
                continue;
            }
            
            Circle tileBounds = {
                {
                    i * currentLevel->destTileW + 0.5 * currentLevel->destTileW,
                    0,
                    j * currentLevel->destTileH + 0.5 * currentLevel->destTileH,
                },
                currentLevel->destTileW * 0.5f
            };
            

            if (circleCircleCollisionCheck(testData->player.hurtbox, tileBounds)){
                printf("Overlap");
                tile = {
                    (float)i * currentLevel->destTileW,
                    (float)j * currentLevel->destTileH,
                    (float)currentLevel->destTileW,
                    (float)currentLevel->destTileH
                };

                tile = testData->c.toScreenSpace(tile);
                
                Vector2 resolution = resolveCircleCollision(testData->player.hurtbox, tileBounds);
                testData->player.updatePos(resolution);
                break;
            }
        }
    }
}

bool Game::checkInteractions(){
    for (auto &interactable: interactables){
        if (circleCircleCollisionCheck(testData->player.hurtbox, interactable.triggerRange)){
            //stateStack.push_back(GameState::GAME_DIALOGUE);
            db.setNewDialogueArray(&interactable.dialogues);
            return true;
        }
    }
    return false;
}

// void Game::getInteractables(){
    // std::vector<Interactable> i;
    // Interactable npc1 = 
// }


LevelMap* Game::loadLevel(const char * levelDir){
    std::string dir(levelDir);


    LevelMap* level = new LevelMap(levelDir, (dir + "/tilemap.png").c_str(), {128,128});
    Vector2 toNewPos = {
        level->playerSpawn.x - testData->player.sprite.x,
        (level->playerSpawn.y - testData->player.sprite.y)/ZY_FACTOR,
    };
    testData->player.updatePos(toNewPos);

    Vector2 npcNewPos = {
         level->npcSpawn.x - testData->npc.sprite.x,
        (level->npcSpawn.y - testData->npc.sprite.y) / ZY_FACTOR,
    };
    testData->npc.updatePos(npcNewPos);

    Vector2 slime0Pos = {
        level->playerSpawn.x + 1000 - testData->slime[0].sprite.x,
        (level->playerSpawn.y + 200 - testData->slime[0].sprite.y) / ZY_FACTOR,
    };
    testData->slime[0].updatePos(slime0Pos);

    Vector2 slime1Pos = {
    level->playerSpawn.x + 2000 - testData->slime[1].sprite.x,
    (level->playerSpawn.y - 200 - testData->slime[1].sprite.y) / ZY_FACTOR,
    };
    testData->slime[1].updatePos(slime1Pos);

    Vector2 slime2Pos = {
    level->playerSpawn.x + 3000 - testData->slime[2].sprite.x,
    (level->playerSpawn.y - 500 - testData->slime[2].sprite.y) / ZY_FACTOR,
    };
    testData->slime[2].updatePos(slime2Pos);

    Vector2 bossSlimePos = {
    level->playerSpawn.x + 4000 - testData->slime[3].sprite.x,
    (level->playerSpawn.y - 600 - testData->slime[3].sprite.y) / ZY_FACTOR,
    };
    testData->slime[3].updatePos(bossSlimePos);

    return level;
}

void Game::loadInteractable(const char *file){
    Lexer l;
    l.loadFile(file);
    int x = currentLevel->destTileW * l.skipAndParseInt();
    int y = currentLevel->destTileH * l.skipAndParseInt();
    int w = l.skipAndParseInt();
    int h = l.skipAndParseInt();
    
    l.skipCurrentLine();
    auto spriteFile = l.parseString("\r\n");

    char buffer[50];
    copyToArray(spriteFile, buffer, sizeof(buffer));
    
    int spriteW = l.skipAndParseInt();
    int spriteH = l.skipAndParseInt();


    interactables.push_back(Interactable(buffer, spriteW, spriteH));

    int index = interactables.size() - 1;
    interactables[index].spriteRect.x = x;
    interactables[index].spriteRect.y = y;
    interactables[index].spriteRect.width = w;
    interactables[index].spriteRect.height = h;

    interactables[index].triggerRange.center = {
        interactables[index].spriteRect.x + interactables[index].spriteRect.width * 0.5f,
        0,
        interactables[index].spriteRect.y + interactables[index].spriteRect.height * 0.5f,
    };
    interactables[index].triggerRange.r = interactables[index].spriteRect.width * 0.6f;

    l.skipCurrentLine();
    auto animName = l.parseString(":");
    int start = l.skipAndParseInt();
    int len = l.skipAndParseInt();
    copyToArray(animName, buffer, sizeof(buffer));


    interactables[index].anim.addAnimation(buffer, start, len, true);
    interactables[index].anim.setDefaultAnimation(buffer);
    interactables[index].anim.setFPS(12);

    l.skipUntil_Inc('"');

    int n = 0;
    while (l.cursor < l.fileSize){
        auto dlg = l.parseString("\r\n\"");
        copyToArray(dlg, interactables[index].dialogues.text[n++], sizeof(interactables[index].dialogues.text[n]));
        if (l.data[l.cursor] == '"')
            break;
        l.skipCurrentLine();
    }

}



void loadLevelFromFile(){

}
