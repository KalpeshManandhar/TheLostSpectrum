#include "tests.h"
#include "../core/animation.h"
#include "../core/slime.h"
#include "../core/collision.h"





AnimationSheet slimeAnimate(){
    AnimationSheet slime ("./assets/slime-Sheet.png", 32, 25);
    slime.addAnimation("idle", 0, 4);
    slime.setFPS(6);
    return slime;
}


TestData testInit(){
    TestData t;
    Rectangle r = {
        0,0,
        200,150
    };
    // t.slime = slimeAnimate();
    t.slime1 = Slime(r);
    r.x += 100;
    t.slime2 = Slime(r);

    // t.c = FollowCamera(&t.slime1.sprite, 1280,720);
    t.c.target = {
        (t.slime1.sprite.x + t.slime1.sprite.width * 0.5f),
        (t.slime1.sprite.y + t.slime1.sprite.height * 0.5f)
    };

    t.c.rotation = 0;
    t.c.offset = {1280*0.5,720*0.5};
    t.c.zoom = 1.0f;
    
    t.p = player();

    Image i = LoadImage("./assets/dungeon.png");
    t.background = LoadTextureFromImage(i);
    UnloadImage(i);

    t.backrect = {-300,-300, 2400,2400};
    return t;
}


void testLoop(TestData *t, float deltaTime){
    t->slime1.resolveChanges();
    t->p.movementCheck();

    if (circleCircleCollisionCheck(t->slime1.hurtbox, t->slime2.hurtbox)){
        printf("Overlap");
        Vector2 r = resolveCircleCollision(t->slime1.hurtbox, t->slime2.hurtbox);
        t->slime1.updatePos(r);
    }

}

void testDisplay(TestData *t, float deltaTime){
    // t->c.update();
    t->c.target = {
        (t->slime1.sprite.x + t->slime1.sprite.width * 0.5f),
        (t->slime1.sprite.y + t->slime1.sprite.height * 0.5f)
    };

    Rectangle screen = {0,0,1280,720};
    Vector2 a = GetWorldToScreen2D({t->backrect.x, t->backrect.y}, t->c);
    Rectangle src = {
        a.x, a.y,
        t->backrect.width, t->backrect.height
    };

    DrawTexturePro(t->background, src, screen, {0,0}, 0, WHITE );

    t->slime1.animate(&t->c, deltaTime);
    t->slime2.animate(&t->c, deltaTime);
    // t->p.draw(t->c.offset);
}

void testFixedLoop(TestData *t, float deltaTime){
    t->slime1.update(deltaTime);
    t->slime2.update(deltaTime);
}

