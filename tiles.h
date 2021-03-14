#pragma once
#include "raylib.h"
#include <iostream>
#define log(x) std::cout << x << std::endl

// N = SCREENWIDTH / SIZE, U = SCREENHEIGHT / SIZE, Y = SIZE, K = Color Depth
template<std::size_t N, std::size_t U, int Y, std::size_t K>
class Tiles{
public:
  Vector2 safePosition = {0.0f, 0.0f};

  // Takes a tilemap and corresponding key (Colours) and draws to a screen

  void drawTiles(int tileset[N][U], int numbers[K], Color colours[K], float xOffset = 0, float yOffset = 0){
    for (int y = 0; y < N; y++){

      for (int x = 0; x < U; x++){

        if (tileset[y][x] != 0){

          Vector2 position = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset};
          Vector2 size = {Y, Y};

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

    for (int y = 0; y < N; y++){

      for (int x = 0; x < U; x++){

        if (tileset[y][x] != 0){

          Vector2 position = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset};

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
    for (int y = 0; y < N; y++){
      for (int x = 0; x < U; x++){

        if (tileset[y][x] != 0){
          Vector2 position = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset};
          Vector2 size = {Y, Y};
          Rectangle base = {position.x, position.y, size.x, size.y};

          if (CheckCollisionRecs(target, base)) return true;

        }

      }

    }

    return false;

  }

  void doCollider(Rectangle &target, int tileset[N][U], float xOffset = 0, float yOffset = 0){
    for (int y = 0; y < N; y++){
      for (int x = 0; x < U; x++){

        if (tileset[y][x] != 0){
          Vector2 position = {(float)(x*Y)+xOffset, (float)(y*Y)+yOffset};
          Vector2 size = {Y, Y};
          Rectangle base = {position.x, position.y, size.x, size.y};

          bool colliding = CheckCollisionRecs(target, base);

          if (colliding){
            target.x = safePosition.x;
            target.y = safePosition.y;
          }
          
        }

      }

    }

    safePosition = {target.x, target.y};

  }

};
