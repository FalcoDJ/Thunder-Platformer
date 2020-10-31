#include "Thunder.hpp"

void Thunder::NewBG(std::string _path2S)
{
    delete m_Background;
    olc::Sprite* BGprite = new olc::Sprite(_path2S);

    m_Background = new olc::Decal(BGprite);
}