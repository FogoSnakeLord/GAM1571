#pragma once
#include "Framework.h"
#include <string>

struct SpriteInfo {
    std::string name;
    fw::vec2 UvScale;
    fw::vec2 UvOffset;
    SpriteInfo(std::string n, fw::vec2 UvS, fw::vec2 UvO) :name(n), UvScale(UvS), UvOffset(UvO) {}
};
class SpriteSheet
{
public:
    SpriteSheet();
    ~SpriteSheet();
    SpriteInfo* GetSpriteInfo(std::string name);
protected:
    std::vector <SpriteInfo*> m_SpriteList;
};

