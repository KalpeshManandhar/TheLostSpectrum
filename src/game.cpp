#include "game.h"
#include <iostream>

#include "player.cpp"
#include "tests/tests.h"



Game::Game(unsigned int width, unsigned int height):
	State(GAME_ACTIVE), Width(width), Height(height){

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


void Game::ProcessInput(float dt) {


}

void Game::Update( float dt)
{
    DrawTexture(testData->background, 0, 0, WHITE);
    
     testLoop(testData, dt);
     testDisplay(testData, dt);
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

