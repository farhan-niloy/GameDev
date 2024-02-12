#include "../include/raylib.h"

int main() {

  // Window Dimensions
  const int WindowHeight = 700;
  const int WindowWidth = 1400;

  // Initialize the Window
  InitWindow(WindowWidth, WindowHeight, "Dapper Dasher");

  int velocity = 0;

  // Gravity (Pixels/s)/s
  const int Gravity = 1000;
  const int jumpVal = -100;

  // Nebula Variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  Rectangle nebRec = {0.0f, 0.0f, static_cast<float>(nebula.width) / 8, static_cast<float>(nebula.height) / 8};
  Vector2 nebPos = {static_cast<float>(WindowWidth), static_cast<float>(WindowHeight) - nebRec.height};

  // Nebula X velocity (pixels/s)
  int nebVel = -600;

  // Scarfy Variables
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  Rectangle scarfyRec;
  scarfyRec.width = static_cast<float>(scarfy.width) / 6;
  scarfyRec.height = static_cast<float>(scarfy.height);
  scarfyRec.x = 0;
  scarfyRec.y = 0;
  Vector2 scarfyPos;
  scarfyPos.x = static_cast<float>(WindowWidth) / 2 - scarfyRec.width / 2;
  scarfyPos.y = static_cast<float>(WindowHeight) - scarfyRec.height;

  // Animation Frame 
  int frame = 0;

  bool isInAir = false;

  // Amount of Time Before We Update the Animation Frame
  const float updateTime = 1.0f / 15.0f;
  float runningTime = 0.0f;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {

    // Start Drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // Delta Time (time since last frame)
    float dT = GetFrameTime();

    // Ground Check
    if (scarfyPos.y >= WindowHeight - scarfyRec.height) {
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

    // Update Nebula Position
    nebPos.x += nebVel * dT;

    // Update Scarfy Position
    scarfyPos.y += velocity * dT;

    if (!isInAir) {
      // Update Running Time 
      runningTime += dT;

      if (runningTime >= updateTime) {
        runningTime = 0.0f;

        // Update Animation Frame 
        scarfyRec.x = frame * scarfyRec.width;
        frame++;
        if (frame > 5) {
          frame = 0;
        }
      }
    }

    // Draw Nebula
    DrawTextureRec(nebula, nebRec, nebPos, WHITE);

    // Draw Scarfy
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // Stop Drawing
    EndDrawing();

  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);

  CloseWindow();

  return 0;
}
