#include "Player.hpp"

Player::Player()
{
    //Define sprite stuff
    m_PathToSprite = "assets/Player/Sprites.png";
    size = {24,24};
    m_FramesPerRow = 10;
    m_FramesPerCol = 1;
    m_MAX_Frames = m_FramesPerRow * m_FramesPerCol;
    m_CurFrame = 0;
    m_SpriteData = RectF({0,0},{24,24});

    //Initialize some stuff
    m_OnGround = false;

    //Define speed stuff
    m_MAX_Acceleration = {300, 700};
    m_Acceleration = {75, 62};
    m_JumpSpeed = 600;
}

bool Player::handleInput(olc::PixelGameEngine* pge)
{
    m_JustJumped = false;

    if (pge->GetKey(olc::Key::SPACE).bHeld && m_OnGround) //Jump
    {
        m_JustJumped = true;
        m_IsJumping = true;
    }
    else
    {
        m_IsJumping = false;
    }

    if (pge->GetKey(olc::Key::LEFT).bHeld) //Move Left
    {
        m_MovingLeft = true;
    }
    else
    {
        m_MovingLeft = false;
    }
    if (pge->GetKey(olc::Key::RIGHT).bHeld) //Move Right
    {
        m_MovingRight = true;
    }
    else
    {
        m_MovingRight = false;
    }
    

    return m_JustJumped;
}