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


    Image i = LoadImage("./assets/dungeon.png");
    ImageResize(&i, 1280, 720);
    testData->background = LoadTextureFromImage(i);
    UnloadImage(i);
}


DialogueArray d = {
    "I am mad scientist.",
    "It's so cool",
    "Sonuvabitch"
};

void Game::ProcessInput(float dt) {
    std::cout << stateStack.back();
    switch (stateStack.back())
    {
    case GAME_DIALOGUE:
        if (IsKeyPressed(KEY_Q)){
            if (!db.nextDlg()){
                stateStack.pop_back();
            }
        }
        break;
    case GAME_ACTIVE:
        if (IsKeyPressed(KEY_Q)){
            stateStack.push_back(GameState::GAME_DIALOGUE);
            db.setNewDialogueArray(&d);
            break;
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
            level->displayBase(&testData->c);
            
            testDisplay(testData, dt);
            level->displayOverlay(&testData->c);
            DrawRectangleLinesEx(tile, 15, WHITE);

            break;
        
        case GAME_DIALOGUE:
            db.show(dt);
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
    
    Vector2 worldPos = {testData->player.hurtbox.center.x,testData->player.hurtbox.center.z};
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
            tile = {
                i * level->destTileW + 0.5f * level->destTileW,
                j * level->destTileH + 0.5f * level->destTileH,
                (float)level->destTileW,
                (float)level->destTileH
            };

            tile = testData->c.toScreenSpace(tile);

            if (circleCircleCollisionCheck(testData->player.hurtbox, tileBounds)){
                printf("Overlap");
                Vector2 resolution = resolveCircleCollision(testData->player.hurtbox, tileBounds);
                testData->player.updatePos(resolution);
                break;
            }
        }
    }
}

void Game::checkInteractions(){
    for (auto interactable: interactables){
        if (circleCircleCollisionCheck(testData->player.hurtbox, interactable.triggerRange)){
            stateStack.push_back(GameState::GAME_DIALOGUE);
            db.setNewDialogueArray(&interactable.dialogues);
            break;
        }
    }
}

// void Game::getInteractables(){
    // std::vector<Interactable> i;
    // Interactable npc1 = 
// }

void Game::loadLevel(){
    level = new LevelMap("./assets/levelmaps/levelA", "./assets/levelmaps/tilemap.png", {128,128});
    Vector2 toNewPos = {
        level->playerSpawn.x - testData->player.sprite.x,
        (level->playerSpawn.y - testData->player.sprite.y)/ZY_FACTOR,
    };
    // testData->player.updatePos(toNewPos);
}