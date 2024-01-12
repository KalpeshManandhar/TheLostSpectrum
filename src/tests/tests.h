#pragma once

#include "../core/animation.h"
#include "../core/slime.h"

struct TestData{
    Slime slime1;
    Slime slime2;
};
TestData testInit();
void testLoop(TestData *t, float deltaTime);
void testDisplay(TestData *t, float deltaTime);
void testFixedLoop(TestData *t, float deltaTime);





