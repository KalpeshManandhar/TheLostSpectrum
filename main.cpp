#include <raylib.h>
#include <raymath.h>

#include <stdint.h>
#include "splashScreen.cpp"
struct Window{
    int w,h;
};




int main(void){
    int width = 1280;
    int height = 720;

    Window w = {
        1280, 720,
    };
    InitWindow(width, height, "The Lost Spectrum");


    splashScreen ss("TEAM DOTS PRESENTS", width, height);
    ss.displaySplashScreen(BLACK, RAYWHITE);
    
    splashScreen ss2("THE LOST SPECTRUM", width, height);
    ss2.displaySplashScreen(WHITE, BLACK);

    SetTargetFPS(60);

    float accumulator = 0;

    while (!WindowShouldClose()){
        float deltaTime = GetFrameTime();
        accumulator += deltaTime;
        
        // fixed dt for fixed time updates
        const float FIXED_DT = 0.002f;

        while(accumulator >= FIXED_DT){
            // update physics and stuff

            accumulator -= FIXED_DT;
        }

        BeginDrawing();
        Color background = {
            0,0,0,255
        };

        ClearBackground(background);
        DrawText("INITIAL CONVERSATION STARTS", static_cast<int>((width/2)-250), static_cast<int>(height/2), 50, WHITE);
        
        
        EndDrawing();

    }
    return 0;
}
