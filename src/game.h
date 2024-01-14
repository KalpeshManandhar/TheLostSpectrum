#pragma once

#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include <stack>
#include "tests/tests.h"
#include "./core/interactable.h"
#include "./core/level.h"
#include "./core/riddle.h"

enum GameState {
	GAME_ACTIVE,
	GAME_DIALOGUE,
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

	std::vector<GameState> stateStack;


	std::vector<Interactable> interactables;
	DialogueBox db;
	riddle r;

	LevelMap *level1;	
	LevelMap *level2;	
	LevelMap *currentLevel;	

	int shardsCollected = 1;
	Shader filterShader;

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

	bool checkInteractions();
	LevelMap *loadLevel(const char * leveldir);
	void loadInteractable(const char *fil);


	//reset
	void ResetLevel();
	void ResetPlayer();

	void fixedLoop(float dt);

	float timer;
	int slimehits[3];
};

#endif // !1
