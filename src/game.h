#pragma once

#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include "tests/tests.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_OVER,
	GAME_RIDDLE,
	HELP_MENU
};

class Game{
public:
	GameState State;
	TestData* testData;

	unsigned int Width, Height;

	//std::vector<GameLevel> Levels;
	//unsigned int Level1;
	//unsigned int Lives;

	Game(unsigned int wWidth, unsigned int wHeight);
	~Game();


	void Init(); //for loading all the textures or levels

	//game loop
	void ProcessInput(float dt);
	void Update( float dt);
	void DoCollitions();


	//reset
	void ResetLevel();
	void ResetPlayer();

	void fixedLoop(float dt);
};

#endif // !1
