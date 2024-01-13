#pragma once

#include "../core/animation.h"
#include "../core/slime.h"
// #include "../core/camera.h"

struct TestData{
    Slime slime1;
    Slime slime2;
    FollowCamera c;
    // Camera2D c;
    Texture2D background; 
    Rectangle backrect; 
    Player player;
    Wizard wizard;
    NPC npc;
};
TestData* testInit();
void testLoop(TestData *t, float deltaTime);
void testDisplay(TestData *t, float deltaTime);
void testFixedLoop(TestData *t, float deltaTime);





