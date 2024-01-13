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

void Game::Update( float dt)
{
    for (auto gs: stateStack){
        switch (gs)
        {
        case GAME_ACTIVE:
            DrawTexture(testData->background, 0, 0, WHITE);
            
            testDisplay(testData, dt);
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