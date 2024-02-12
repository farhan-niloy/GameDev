#include "include/raylib.h"

int main(void) {

  InitWindow(1024, 768, "Hello World!");

    while (WindowShouldClose() == false) {

        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }


    return 0;
}

