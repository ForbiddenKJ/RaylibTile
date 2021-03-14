#include "raylib.h"
#include "tiles.h"

#include <iostream>

#define log(x) std::cout << x << std::endl

int main(){

  // Define our constants

  const int SCREENHEIGHT = 512;
  const int SCREENWIDTH = 800;
  const Color BACKGROUND = {28, 28, 28, 255};

  // Define our tilemap (Our tilemap is a tile and can be reused as a collision map) (Each number represents 32x32 chunk of the screen)

  int tilemap[16][25] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}};

  // Init our window

  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Window");
  SetTargetFPS(60);

  // Create our Tiles class
  // N = SCREENWIDTH / SIZE, U = SCREENHEIGHT / SIZE, Y = SIZE, K = Color Depth

  Tiles<16, 25, 32, 1> mainTile;

  // Nums & Textures index

  int nums[1] = {1};
  Texture2D textures[1] = {LoadTexture("./exampleTexture.png")};

  // Player Rectangle

  Rectangle player = {0.0f, 0.0f, 32.0f, 32.0f};
  bool colliding = false;

  while(!WindowShouldClose()){

    // Basic Movement

    if (IsKeyDown(KEY_W)) player.y -= 2.0f;
    if (IsKeyDown(KEY_S)) player.y += 2.0f;

    if (IsKeyDown(KEY_D)) player.x += 2.0f;
    if (IsKeyDown(KEY_A)) player.x -= 2.0f;

    // Force player not to be able to pass through objects in tilemap

    mainTile.doCollider(player, tilemap);

    // Start drawring and clear screen

    BeginDrawing();
    ClearBackground(BACKGROUND);

    // Draw textures

    mainTile.drawTiles(tilemap, nums, textures);

    // Draw player

    DrawRectangleV((Vector2){player.x, player.y},(Vector2){32.0f, 32.0f}, RAYWHITE);

    // Draw FPS

    DrawFPS(0, 0);

    // End drawring

    EndDrawing();
  }

  CloseWindow();
}
