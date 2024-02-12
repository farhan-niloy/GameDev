#include "../include/raylib.h"

int main() {
    // Window Dimension
    int width{1400};
    int height{700};
    Color darkGreen = {0, 100, 0, 255};

    // Circle Coordinates
    int circle_x = static_cast<int>(width / 2);
    int circle_y = static_cast<int>(height / 2);

    InitWindow(width, height, "Farhan's Window");

    SetTargetFPS(60);
    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(darkGreen);

        // Game Logic Begins
        DrawCircle(circle_x, circle_y, 100, RED);

        if (IsKeyDown(KEY_D)) {
            circle_x = circle_x + 10;
        } 

        if (IsKeyDown(KEY_A)) {
            circle_x = circle_x - 10;
        } 
         
        if (IsKeyDown(KEY_W)) {
            circle_y  -= 10;
        } 

        if (IsKeyDown(KEY_S)) {
            circle_y += 10;
        } 

        // Game Logic Ends

        EndDrawing();
    }


    return 0;
}
