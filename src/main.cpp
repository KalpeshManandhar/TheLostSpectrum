#include <raylib.h>
#include <raymath.h>

#include <stdint.h>

#include "tests/tests.h"
#include "gifAnim/gifAnim.h"

#include "splashScreen.cpp"
#include "game.h"


struct Window{
    int w,h;
};


int main(void){
    unsigned int width = 1280;
    unsigned int height = 720;

    Window w = {
        1280, 720,
    };

    InitWindow(width, height, "The Lost Spectrum");

    Game TheLostSpectrum(width, height);


    splashScreen ss("TEAM DOTS PRESENTS", 50, width, height, 3);
    ss.displaySplashScreen(WHITE, BLACK, "./assets/boat.png", 800, 600, 0, 21);
    
    splashScreen ss2("THE LOST SPECTRUM", 50,  width, height, 3);
    ss2.displaySplashScreen(BLACK, RAYWHITE, "./assets/boat.png", 800, 600, 21,41 );

    splashScreen ss3("In the realm of Chromaterra, where colors \n once danced harmoniously across vibrant \n landscapes, a tale unfolds.",40, width, height - 300, 6);
    ss3.displaySplashScreen(WHITE, BLACK, "./assets/staticboat.png", 600, 437, 0, 35);

    //splashScreen ss4("In the realm of Chromaterra, where colors \n once danced harmoniously across vibrant \n landscapes, a tale unfolds.", 30, width, height - 400, 6);
    //ss4.displayConvo(BLACK, WHITE, "./assets/bg.png");

    SetTargetFPS(60);
    
    bool initialAnim = true;
    float accumulator = 0;

    while (!WindowShouldClose()){
       
        float deltaTime = GetFrameTime();
        

        accumulator += deltaTime;
        // fixed dt for fixed time updates
        const float FIXED_DT = 0.002f;

        while(accumulator >= FIXED_DT){
             //update physics and stuff
           // testFixedLoop(&testData, deltaTime);
            accumulator -= FIXED_DT;
        }

        BeginDrawing();
        Color background = {
            0,0,0,255
        };

        ClearBackground(background);

        TheLostSpectrum.ProcessInput(deltaTime);
        TheLostSpectrum.Update(deltaTime);

        EndDrawing();

    }
    return 0;
}
