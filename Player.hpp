#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Creature.hpp"
#include <iostream>

class Player : public Creature
{
public:
    Player();
    ~Player(){}
    bool handleInput(olc::PixelGameEngine *pge) override;

private:

};

#endif