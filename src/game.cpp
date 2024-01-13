#include "game.h"
#include <iostream>

#include "player.cpp"
#include "tests/tests.h"
#include "core/collision.h"

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
    loadLevel();

    filterShader = LoadShader(0, "./src/shaders/rgb.fs");

    memset(slimehits, 0, 3 * sizeof(int));
    slimeHit = false;
    //Image i = LoadImage("./assets/dungeon.png");
    //ImageResize(&i, 1280, 720);
    //testData->background = LoadTextureFromImage(i);
    //UnloadImage(i);
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
            stateStack.push_back(GameState::GAME_DIALOGUE);
            db.setNewDialogueArray(&d);
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
    for (auto gs: stateStack){
        switch (gs)
        {
        case GAME_ACTIVE:
            // DrawTexture(testData->background, 0, 0, WHITE);

            testData->c.update();


            level->displayBase(&testData->c, shardsCollected);
            displaySlime(testData, dt);
            

            testData->player.animate(&testData->c, dt);
            level->displayOverlay(&testData->c, shardsCollected);
            DrawRectangleLinesEx(tile, 12, WHITE);


            if(circleCircleCollisionCheck(testData->slime[0].hurtbox, testData->player.hurtbox)) {

                if (testData->player.isAttacking) {
                    /*slimeHit = true;*/
                    testData->slime[0].playDead(&testData->c, dt);
                    testData->slime[0].isActive = false;
                    std::cout << "slime hit = " <<slimeHit<<"\n";
                }
            }
            if (circleCircleCollisionCheck(testData->slime[1].hurtbox, testData->player.hurtbox)) {

                if (testData->player.isAttacking) {
                    /*slimeHit = true;*/
                    testData->slime[1].playDead(&testData->c, dt);
                    testData->slime[1].isActive = false;
                    std::cout << "slime hit = " << slimeHit << "\n";
                }
            }
            if (circleCircleCollisionCheck(testData->slime[2].hurtbox, testData->player.hurtbox)) {

                if (testData->player.isAttacking) {
                    /*slimeHit = true;*/
                    testData->slime[2].playDead(&testData->c, dt);
                    testData->slime[2].isActive = false;
                    std::cout << "slime hit = " << slimeHit << "\n";
                }
            }
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

    
    //Player.draw({0,0});
    //Player.movementCheck();

    //DrawText("INITIAL CONVERSATION STARTS", static_cast<int>((Width / 2) - 250), static_cast<int>(Height / 2), 50, WHITE);
    
}

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
    Vector2 tilePos = {worldPos.x/level->destTileW, worldPos.y/level->destTileH};

    int startTileX = Max(0, tilePos.x - 4);
    int startTileY = Max(0, tilePos.y - 4);
    int endTileX = Min(level->w, tilePos.x + 4);
    int endTileY = Min(level->h, tilePos.y + 4);

    for (int j = startTileY; j<endTileY; j++){
        for (int i = startTileX; i<endTileX; i++){
            if (level->collisionMap[j * level->w + i] == -1){
                continue;
            }
            
            Circle tileBounds = {
                {
                    i * level->destTileW + 0.5 * level->destTileW,
                    0,
                    j * level->destTileH + 0.5 * level->destTileH,
                },
                level->destTileW * 0.5f
            };
            

            if (circleCircleCollisionCheck(testData->player.hurtbox, tileBounds)){
                printf("Overlap");
                tile = {
                    (float)i * level->destTileW,
                    (float)j * level->destTileH,
                    (float)level->destTileW,
                    (float)level->destTileH
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
    //for (auto interactable: interactables){
        if (circleCircleCollisionCheck(testData->player.hurtbox, testData->npc.hurtbox)){
            //stateStack.push_back(GameState::GAME_DIALOGUE);
            //db.setNewDialogueArray(&d);
        //    db.setNewDialogueArray(&interactable.dialogues);
        //    break;}
        
            return true;
    }
        return false;
}

// void Game::getInteractables(){
    // std::vector<Interactable> i;
    // Interactable npc1 = 
// }

void Game::loadLevel(){
    level = new LevelMap("./assets/levelmaps/levelA", "./assets/levelmaps/levelA/tilemap.png", {128,128});
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
}