#pragma once
#include "raylib.h"
#include <iostream>
#define log(x) std::cout << x << std::endl

// N = SCREENWIDTH / SIZE, U = SCREENHEIGHT / SIZE, Y = SIZE, K = Color Depth
template<std::size_t N, std::size_t U, int Y, std::size_t K>
class Tiles{
public:
  // Safe position location variable

  Vector2 safePosition = {0.0f, 0.0f};

  // Takes a tilemap and corresponding key (Colours) and draws to a screen

  void drawTiles(int tileset[N][U], int numbers[K], Color colours[K], float xOffset = 0, float yOffset = 0){

    // Get each item in the tilemap and evaluate individually

    for (int y = 0; y < N; y++){
      for (int x = 0; x < U; x++){

        // Check if its a valid tile

        if (tileset[y][x] != 0){

          // Calculate the position and size of our tile object

          Vector2 position = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset};
          Vector2 size = {Y, Y};

          // Compare each in tileset to numbers to find colour index

          for (int z = 0; z < K; z++){

            if (tileset[y][x] == numbers[z]){

              DrawRectangleV(position, size, colours[z]);

            }

          }

        }

      }

    }

  }

  // Takes a tilemap and corresponding key (Textures) and draws to a screen

  void drawTiles(int tileset[N][U], int numbers[K], Texture2D textures[K], float xOffset = 0, float yOffset = 0, Color tint = WHITE){

    // Get each item in the tilemap and evaluate individually

    for (int y = 0; y < N; y++){
      for (int x = 0; x < U; x++){

        // Check if its a valid tile

        if (tileset[y][x] != 0){

          // Calculate the position of our tile object

          Vector2 position = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset};

          // Compare each in tileset to numbers to find texture index

          for (int z = 0; z < K; z++){

            if (tileset[y][x] == numbers[z]){

              DrawTextureV(textures[z], position, tint);

            }

          }

        }

      }

    }

  }

  // Takes a collisionmap and target and checks if they are colliding

  bool isColliding(Rectangle target, int tileset[N][U], float xOffset = 0, float yOffset = 0){

    // Get each item in the collisionmap and evaluate individually

    for (int y = 0; y < N; y++){
      for (int x = 0; x < U; x++){

        // Check if our value is collidable

        if (tileset[y][x] != 0){

          // Calculate the position and size of our collidable object

          Rectangle base = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset, Y, Y};

          // Return true if one of out objects in colliding

          if (CheckCollisionRecs(target, base)) return true;

        }

      }

    }

    return false;

  }

  // Takes an object and a collisionmap and prevents the object from moving through the collision map

  void doCollider(Rectangle &target, int tileset[N][U], float xOffset = 0, float yOffset = 0){

    // Get each item in the collisionmap and evaluate individually

    for (int y = 0; y < N; y++){
      for (int x = 0; x < U; x++){

        // Check if our value is collidable

        if (tileset[y][x] != 0){

          // Calculate the position and size of our collidable object

          Rectangle base = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset, Y, Y};

          // If they are colliding move target to last non-colliding position

          if (CheckCollisionRecs(target, base)){
            target.x = safePosition.x;
            target.y = safePosition.y;
          }

        }

      }

    }

    // Set latest non-colliding position

    safePosition = {target.x, target.y};

  }

};
