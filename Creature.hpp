#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "HPP/olcPixelGameEngine.h"
#include "HPP/Shapes.hpp"
#include "HPP/Clock.hpp"

class Creature : public RectF
{
public:
    Creature(){};
    ~Creature(){delete m_Sprite, m_Decal;}
    
    virtual bool handleInput(olc::PixelGameEngine *pge); //Define in derived class
    virtual void animate();  //Define in derived class
    void update(float ElapsedTime);
    virtual void updateAi(RectF& Targ){};
    void drawSelf(olc::PixelGameEngine *pge, VectorF Camera);

    void Setup();

    RectF getSpriteD();

    virtual void spawn(VectorI _start);
    virtual void reset(); //TODO - Edit this later

    void stopLeft(float newXl);
    void stopRight(float newXr);
    void stopFalling(float floorY);
    void fall();

    void resolveCollision(Rect &Targ) override;

protected:
    std::string m_PathToSprite;
    RectF m_SpriteData;
    olc::Sprite* m_Sprite = nullptr;
    olc::Decal* m_Decal = nullptr;
    
    int m_FramesPerRow;
    int m_FramesPerCol;
    int m_MAX_Frames;
    int m_CurFrame;

    VectorF m_Acceleration;
    VectorF m_MAX_Acceleration;
    float m_JumpSpeed;

    float m_Health;
    float m_MAX_Health;

    //Status variables
    bool m_JustJumped;
    bool m_IsJumping;
    bool m_OnGround;
    Clock m_JumpTimer;

    bool m_MovingLeft;
    bool m_MovingRight;
    bool m_UpPressed;
    bool m_DownPressed;
};

#endif