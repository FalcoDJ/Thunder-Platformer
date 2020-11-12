#ifndef SPRITEANIMATOR_HPP
#define SPRITEANIMATOR_HPP

#include "olcPixelGameEngine.h"
#include "Shapes.hpp"

template <typename num>
void DrawDecalFrame(olc::PixelGameEngine *pge, olc::Decal *Decal, Vector<num> Pos, Vector<num> SpriteSize, VectorI framesPer, int currentFrame, Vector<num> Camera = {0,0})
{
  int spriteSheetRow = (currentFrame / framesPer.x);
  int spriteSheetColumn = (currentFrame % framesPer.x);
  int spriteSheetX = (spriteSheetColumn * SpriteSize.x);
  int spriteSheetY = (spriteSheetRow * SpriteSize.y);

  pge->DrawPartialDecal({float(Pos.x - Camera.x), float(Pos.y - Camera.y)}, Decal, {float(spriteSheetX),float(spriteSheetY)}, {float(SpriteSize.x), float(SpriteSize.y)});
}

template <typename num>
void DrawSpriteFrame(olc::PixelGameEngine *pge, olc::Sprite *Sprite, Vector<num> Pos, Vector<num> SpriteSize, VectorI framesPer, int currentFrame, Vector<num> Camera = {0,0})
{
  int spriteSheetRow = (currentFrame / framesPer.x);
  int spriteSheetColumn = (currentFrame % framesPer.x);
  int spriteSheetX = (spriteSheetColumn * SpriteSize.x);
  int spriteSheetY = (spriteSheetRow * SpriteSize.y);

  pge->DrawPartialSprite({float(Pos.x - Camera.x), float(Pos.y - Camera.y)}, Sprite, {float(spriteSheetX),float(spriteSheetY)}, {float(SpriteSize.x), float(SpriteSize.y)});
}

#endif
