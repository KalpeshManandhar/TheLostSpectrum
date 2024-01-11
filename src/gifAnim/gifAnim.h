#pragma once

#include "../core/animation.h"

struct initialAnimation {
    AnimationSheet ocean;
};


initialAnimation gifInit(const char* gifPath, int singleWidth, int singleHeight, int start, int total);
void gifLoop(initialAnimation* t, float deltaTime);