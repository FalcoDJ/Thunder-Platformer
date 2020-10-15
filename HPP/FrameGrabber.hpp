#ifndef SPRITEANIMATOR_HPP
#define SPRITEANIMATOR_HPP

#include "olcPixelGameEngine.h"
#include "Shapes.hpp"

template <typename num>
void DrawDecalFrame(olc::PixelGameEngine *pge, olc::Decal *Decal, Vector<num> Pos, Rect<num> SpriteSize, int framesPerRow, int framesPerColumn, int currentFrame, Vector<num> Camera = {0,0})
{
  int spriteSheetRow = (currentFrame / framesPerRow) | 0;
  int spriteSheetColumn = (currentFrame % framesPerRow) | 0;
  int spriteSheetX = (spriteSheetColumn * SpriteSize.size.x);
  int spriteSheetY = (spriteSheetRow * SpriteSize.size.y);

  pge->DrawPartialDecal({float(Pos.x - Camera.x), float(Pos.y - Camera.y)}, Decal, {float(spriteSheetX),float(spriteSheetY)}, {float(SpriteSize.size.x), float(SpriteSize.size.y)});
}

#endif
