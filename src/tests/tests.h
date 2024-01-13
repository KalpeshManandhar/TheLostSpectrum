#pragma once

#include "../core/animation.h"
#include "../core/slime.h"
// #include "../core/camera.h"

struct TestData{
    Slime* slime;

    FollowCamera c;
    // Camera2D c;
    Texture2D background; 
    Rectangle backrect; 
    Player player;
    Wizard wizard;
    NPC npc;

    compass comp;
    int tinySlimeHits;
    ~TestData();
};
TestData* testInit();
void testLoop(TestData *t, float deltaTime);
void testDisplay(TestData *t, float deltaTime);
void testFixedLoop(TestData *t, float deltaTime);
void displaySlime(TestData* t, float deltaTime);