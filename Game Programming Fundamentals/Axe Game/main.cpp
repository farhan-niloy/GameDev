
#include "../include/raylib.h"

int main() {
    // Window Dimension
    int width{1400};
    int height{700};
    Color darkGreen = {0, 100, 0, 255};

    // Circle Coordinates
    int circle_x = 300;
    int circle_y = static_cast<int>(height / 2);
    int circle_radious = 30;
    // Circle Edge
    int l_circle_x { circle_x - circle_radious };
    int r_circle_x { circle_x + circle_radious };
    int u_circle_y { circle_y - circle_radious };
    int d_circle_y { circle_y + circle_radious };

    // Axe Coordinates
    int axe_x = static_cast<int>(width/2);
    int axe_y = static_cast<int>(height/2);
    // Axe Edge 
    int l_axe_x { axe_x };
    int r_axe_x { axe_x + 50};
    int u_axe_y { axe_y };
    int d_axe_y { axe_y + 50};

    int direction{50};

    InitWindow(width, height, "Farhan's Window");

    SetTargetFPS(60);
    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(darkGreen);

        // Game Logic Begins

        // Update the Edges
        l_circle_x = circle_x - circle_radious;
        r_circle_x = circle_x + circle_radious;
        u_circle_y = circle_y - circle_radious;
        d_circle_y = circle_y + circle_radious;
        l_axe_x = axe_x;
        r_axe_x = axe_x + 50;
        u_axe_y = axe_y;
        d_axe_y = axe_y + 50;
        // Update Collision with Axe
        bool collison_w_axe = 
            (d_axe_y >= u_circle_y) && 
            (u_axe_y <= d_circle_y) && 
            (r_circle_x >= l_circle_x) && 
            (l_axe_x <= r_circle_x);

        if (collison_w_axe) {
            DrawText("Game Over!", axe_x-50, axe_y-30, circle_radious, RED);
        } else {
            int circle_radious = 30;
            int axe_length = 50;
            DrawCircle(circle_x, circle_y, circle_radious, RED);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, BROWN);

            // Move the Axe
            axe_y += direction;

            if(axe_y < 0 || axe_y > height) {
                direction = -direction;
            }


            if (IsKeyDown(KEY_D) && circle_x < width) {
                circle_x = circle_x + 15;
            } 

            if (IsKeyDown(KEY_A) && circle_x > 0) {
                circle_x = circle_x - 15;
            } 
             
            if (IsKeyDown(KEY_W) && circle_y > 0) {
                circle_y  -= 15;
            } 

            if (IsKeyDown(KEY_S) && circle_y < height) {
                circle_y += 15;
            } 

            // Game Logic Ends
        }

        EndDrawing();
    }

    return 0;
}

