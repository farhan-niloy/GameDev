
#include "../include/raylib.h"

struct AnimData {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
}; // Don't forget the semicolon to end the struct definition

int main() {

    // Window Dimensions
    const int WindowHeight = 700;
    const int WindowWidth = 1400;

    // Initialize the Window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher");

    int velocity = 0;

    // Gravity (Pixels/s)/s
    const int Gravity = 2000;
    const int jumpVal = -700;

    // Nebula Variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Nebula X velocity (pixels/s)
    int nebVel = -500;

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = static_cast<float>(scarfy.width) / 6;
    scarfyData.rec.height = static_cast<float>(scarfy.height);
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = static_cast<float>(WindowWidth) / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = static_cast<float>(WindowHeight) - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0f / 12.0f;
    scarfyData.runningTime = 0.0f;

    // AnimData for Nebulae
    AnimData nebulae[2]{
            { {0.0f, 0.0f, static_cast<float>(nebula.width) / 8, static_cast<float>(nebula.height) / 8},
              {static_cast<float>(WindowWidth), static_cast<float>(WindowHeight) - static_cast<float>(nebula.height) / 8},
              0, // int frame
              1.0f / 16.0f, // float updateTime
              0 }, //float runningTime
            { {0.0f, 0.0f, static_cast<float>(nebula.width) / 8, static_cast<float>(nebula.height) / 8},
              {static_cast<float>(WindowWidth + 300), static_cast<float>(WindowHeight) - static_cast<float>(nebula.height) / 8},
              0, // int frame
              1.0f / 12.0f, // float updateTime
              0 } //float runningTime
    };

    bool isInAir = false;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Delta Time (time since last frame)
        float dT = GetFrameTime();

        // Ground Check
        if (scarfyData.pos.y >= WindowHeight - scarfyData.rec.height) {
            // Rectangle is On The Ground
            isInAir = false;
            velocity = 0;
        } else {
            // Apply Gravity
            velocity += Gravity * dT;
            isInAir = true;
        }

        // Check for Jumping
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVal;
        }

        // Update Nebula Positions
        nebulae[0].pos.x += nebVel * dT;
        nebulae[1].pos.x += nebVel * dT;

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

        // Update Scarfy Animation Frame
        if (!isInAir) {
            // Update Running Time
            scarfyData.runningTime += dT;

            if (scarfyData.runningTime >= scarfyData.updateTime) {
                scarfyData.runningTime = 0.0f;

                // Update Animation Frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5) {
                    scarfyData.frame = 0;
                }
            }
        }

        // Update Nebulae Animation Frames
        for (int i = 0; i < 2; ++i) {
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime) {
                nebulae[i].runningTime = 0.0f;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7) {
                    nebulae[i].frame = 0;
                }
            }
        }

        Color color[2]{WHITE, PURPLE};

        // Draw Nebulae
        for (int i = 0; i < 2; ++i) {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, color[i]);
        }

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Stop Drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();

    return 0;
}
