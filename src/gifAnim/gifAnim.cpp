#include "gifAnim.h"
#include "../core/animation.h"


AnimationSheet gifAnimate(const char* _gifPath,int _singleWidth, int _singleHeight, int _st, int _total) {
    AnimationSheet ocean(_gifPath, _singleWidth, _singleHeight );
    ocean.addAnimation("oceanWaves", _st, _total, false);
    ocean.setFPS(6);
    return ocean;
}


initialAnimation gifInit(const char* gifPath, int singleWidth, int singleHeight, int start, int total) {
    initialAnimation t;
    t.ocean = gifAnimate(gifPath, singleWidth, singleHeight, start, total);
    return t;
}


void gifLoop(initialAnimation* t, float deltaTime) {
    Rectangle r = {
        0,0,
        1280,720
    };
    t->ocean.playAnimation("oceanWaves", deltaTime, r);
}
