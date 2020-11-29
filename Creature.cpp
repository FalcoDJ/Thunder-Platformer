#include "Creature.hpp"
#include "HPP/FrameGrabber.hpp"

bool Creature::handleInput(olc::PixelGameEngine *pge)
{
    return true;
}

void Creature::animate()
{
    m_CurFrame++;
    if (m_CurFrame > m_MAX_Frames - 1) m_CurFrame = 0;
}

void Creature::update(float ElapsedTime)
{
    //X axis
    if (m_MovingLeft) //Control moving left
    {
        vel.x -= m_Acceleration.x;
    }
    if (m_MovingRight) //Control moving right
    {
        vel.x += m_Acceleration.x;
    }
    if (vel.x < -m_MAX_Acceleration.x) //Is moving Left
    {
        vel.x = -m_MAX_Acceleration.x;
    }
    if (vel.x > m_MAX_Acceleration.x)  //Is moving Right
    {
        vel.x = m_MAX_Acceleration.x;
    }
    if (vel.x != 0 && !m_MovingLeft && !m_MovingRight) //Drag
    {
        if (vel.x > 0) //is moving right
        {
            vel.x -= m_Acceleration.x;
        }
        else //is moving left
        {
            vel.x += m_Acceleration.x;
        }
        if (vel.x * vel.x < m_Acceleration.x * m_Acceleration.x) //Complete stop if vel.x is too small
        {
            vel.x = 0;
        }
        
    }

    pos.x += vel.x * ElapsedTime;

    //Y axis
    
    if (m_JumpTimer.GetElapsedTime() > 0.036f)//Gravity
    {
        vel.y += m_Acceleration.y;
    }

    if (m_Acceleration.y > m_MAX_Acceleration.y)
    {
        m_Acceleration.y = m_MAX_Acceleration.y;
    }
    if (m_IsJumping) //Jump
    {
        m_JumpTimer.Restart();
        vel.y = -m_JumpSpeed;
        m_OnGround = false;
        m_IsJumping = true;
    }

    //Apply velocities to position
    pos.y += vel.y * ElapsedTime;

    //Handle States
    if (m_State != state::DEFAULT)
    {
        if (m_State == state::INVINSIBLE)
        {
            m_Health = m_MAX_Health;
            if (m_StateTimer.GetElapsedTime() > m_MAX_InvincibleT)
            {
                m_State = state::DEFAULT;
            }
        }
    }

}

void Creature::drawSelf(olc::PixelGameEngine *pge, VectorF Camera)
{
    DrawDecalFrame(pge, m_Decal, pos, m_SpriteData, m_FramesPer, m_CurFrame, Camera, m_Flip);
}

void Creature::Setup()
{
    m_Sprite = new olc::Sprite(m_PathToSprite);
    m_Decal = new olc::Decal(m_Sprite);
}

RectF Creature::getSpriteD()
{
    return m_SpriteData;
}

void Creature::spawn(VectorI _start)
{
    center(_start);
    vel *= 0;
    m_JumpTimer.Restart();
}
void Creature::reset()
{
    vel *= 0;
    
    m_Lives = m_MAX_Lives;
    m_Health = m_MAX_Health;
}

void Creature::stopLeft(float newXl)
{
    pos.x = newXl;
}
void Creature::stopRight(float newXr)
{
    pos.x = newXr - size.x;
}
void Creature::stopFalling(float floorY)
{
    pos.y = floorY - size.y;
    m_OnGround = true;
}
void Creature::fall()
{
    m_OnGround = false;
}

void Creature::resolveCollision(Rect &Targ)
{
    float Hd = center().x - Targ.center().x;
    float Vd = center().y - Targ.center().y;
    float Aw = (size.x + Targ.size.x) / 2;
    float Ah = (size.y + Targ.size.y) / 2;

    float overlap_x = Hd * Hd - Aw * Aw;
    float overlap_y = Vd * Vd - Ah * Ah;

    if (overlap_x > overlap_y)
    {
        //If collision happens on X axis
        vel.x = Targ.vel.x;
        
        if (Hd > 0)
        {
            stopLeft(Targ.right());
        }
        else
        {
            stopRight(Targ.pos.x);
        }
    }
    else
    {
        //If collision happens on Y axis
        vel.y = Targ.vel.y;
        
        if (Vd > 0)
        {
            pos.y = Targ.bottom();
        }
        else
        {
            stopFalling(Targ.pos.y);
        }
    }
}
