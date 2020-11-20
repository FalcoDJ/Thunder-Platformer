#include "Player.hpp"

Player::Player()
{
    //Define sprite stuff
    m_PathToSprite = "assets/Player/Sprites.png";
    size = {24,24};
    m_FramesPer = {9, 1};
    m_MAX_Frames = m_FramesPer.x * m_FramesPer.y;
    m_CurFrame = 0;
    m_SpriteData = {24,24};
    m_Flip = olc::Sprite::NONE;

    //Initialize some stuff
    m_OnGround = true;
    m_MAX_Lives = 5;
    m_Lives = 5;

    m_MAX_InvincibleT = 0.096;

    //Define speed stuff
    m_MAX_Acceleration = {300, 200};
    m_Acceleration = {75, 62};
    m_JumpSpeed = 600;
}

bool Player::handleInput(olc::PixelGameEngine* pge)
{
    m_JustJumped = false;

    if ((pge->GetKey(olc::Key::SPACE).bHeld) && m_OnGround) //Jump
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

void Player::animate()
{
    m_CurFrame++;
    if (m_CurFrame > m_MAX_Frames-1) m_CurFrame -= m_MAX_Frames-1;

    if (vel.x < 0 || m_MovingLeft)
    m_Flip = olc::Sprite::HORIZ;
    else if (vel.x > 0 || m_MovingRight)
    m_Flip = olc::Sprite::NONE;
    
}