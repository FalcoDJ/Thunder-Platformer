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
    if (abs(vel.x) > m_MAX_Acceleration.x) //Maximum Velocity
    {
        if (vel.x < 0) //Is moving Left
        {
            vel.x = -m_MAX_Acceleration.x;
        }
        else //Is moving Right
        {
            vel.x = m_MAX_Acceleration.x;
        }
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
        if (abs(vel.x) < m_Acceleration.x) //Precausions!
        {
            vel.x = 0;
        }
        
    }

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
        vel.y = -(m_JumpSpeed);
        m_OnGround = false;
        m_IsJumping = true;
    }

    //Apply velocities to position
    pos += vel * ElapsedTime;

}

void Creature::drawSelf(olc::PixelGameEngine *pge, VectorF Camera)
{
    DrawDecalFrame(pge, m_Decal, pos, m_SpriteData, m_FramesPerRow, m_FramesPerCol, m_CurFrame, Camera);
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
    pos.x = _start.x - size.x / 2;
    pos.y = _start.y - size.y;
    vel *= 0;
    
    m_Health = m_MAX_Health;
}
void Creature::reset()
{
    vel *= 0;
    
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
    float Aw = (size.x + Targ.size.x) * 0.5;
    float Ah = (size.y + Targ.size.y) * 0.5;

    float overlap_x = Aw - abs(Hd);
    float overlap_y = Ah - abs(Vd);

    if (overlap_x < overlap_y)
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
            pos.y += Targ.bottom() - pos.y;
        }
        else
        {
            stopFalling(Targ.pos.y);
        }
    }
}
