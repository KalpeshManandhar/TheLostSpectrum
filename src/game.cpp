#include "game.h"
#include <iostream>

#include "player.cpp"
#include "tests/tests.h"

player p1;


Game::Game(unsigned int width, unsigned int height):
	State(GAME_ACTIVE), Width(width), Height(height){

}


Game::~Game() {

}


void Game::Init() {
    
}


void Game::ProcessInput(float dt) {


}

void Game::Update( float dt)
{
    
    // testLoop(&testData, dt);
    // testDisplay(&testData, dt);
    // p1.draw();
    // p1.movementCheck();

    DrawText("INITIAL CONVERSATION STARTS", static_cast<int>((Width / 2) - 250), static_cast<int>(Height / 2), 50, WHITE);

}

void Game::DoCollitions() {


}

void Game::ResetLevel()
{
}

void Game::ResetPlayer()
{
}

