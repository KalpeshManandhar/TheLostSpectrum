#pragma once

#include "../core/animation.h"
#include "../core/slime.h"
#include "../core/camera.h"
#include "../player.cpp"

struct TestData{
    Slime slime1;
    Slime slime2;
    player p;
    FollowCamera c;
};
TestData testInit();
void testLoop(TestData *t, float deltaTime);
void testDisplay(TestData *t, float deltaTime);
void testFixedLoop(TestData *t, float deltaTime);





