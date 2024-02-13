#include "../include/raylib.h"

struct AnimData {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
}; 

bool isOnGround(AnimData data, int windowHeight) {
  return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
  // Update running Time
  data.runningTime += deltaTime;
  if (data.runningTime >= data.updateTime){
    data.runningTime = 0.0;
    // update Animation frame
    data.rec.x = data.frame * data.rec.width;
    data.frame++;
    if(data.frame > maxFrame) {
      data.frame = 0;
    }
  }
  return data;
}

int main() {

    // Window Dimensions
    const int WindowHeight = 700;
    const int WindowWidth = 1400;

    // Initialize the Window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher");

    int velocity = 0;

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    // Gravity (Pixels/s)/s
    const int Gravity = 2300;
    const int jumpVal = -650;

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

    // AnimData
    const int sizeOFNebulae{100};
    AnimData nebulae[sizeOFNebulae]{};

    // Initialize Nebulae
    for (int i = 0; i < sizeOFNebulae; ++i)
{
    nebulae[i].rec.x = 0.0f;
    nebulae[i].rec.y = 0.0f;
    nebulae[i].rec.width = static_cast<float>(nebula.width) / 8;
    nebulae[i].rec.height = static_cast<float>(nebula.height) / 8;
    nebulae[i].pos.y = static_cast<float>(WindowHeight) - static_cast<float>(nebula.height) / 8;
    nebulae[i].frame = 0;
    nebulae[i].runningTime = 0.0f;
    nebulae[i].updateTime = 1.0f / 16.0f;
    nebulae[i].pos.x = static_cast<float>(WindowWidth) + i * 300;
}

    bool isInAir = false;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        // Start Drawing:
        BeginDrawing();
        ClearBackground(WHITE);

        // Delta Time (time since last frame)
        float dT = GetFrameTime();

        bgX -= 20 * dT;
        if(bgX <= -background.width*9) {
          bgX = 0.0;
        }

        // Draw the background
        Vector2 big1Pos{bgX, 0.0f};
        DrawTextureEx(background, big1Pos, 0.0f, 9.0f, WHITE);
        Vector2 big2Pos{bgX + background.width*9, 0.0};
        DrawTextureEx(background, big2Pos, 0.0, 9.0f, WHITE);

        // Ground Check
        if (isOnGround(scarfyData, WindowHeight)) {
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
        for(int i = 0; i < sizeOFNebulae; i++) {
          nebulae[i].pos.x += nebVel * dT;
        }

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

        // Update Scarfy Animation Frame
        if (!isInAir) 
        {
          scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        // Update Nebulae Animation Frames
        for (int i = 0; i < sizeOFNebulae; ++i)
        {
          nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        Color color[3]{WHITE, PURPLE, ORANGE};

        // Draw Nebulae
        for (int i = 0; i < sizeOFNebulae; ++i) {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, color[i]);
        }

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Stop Drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);

    CloseWindow();

    return 0;
}
