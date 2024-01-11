#pragma once

#include "../core/animation.h"

struct TestData{
    AnimationSheet slime;
};
TestData testInit();
void testLoop(TestData *t, float deltaTime);





