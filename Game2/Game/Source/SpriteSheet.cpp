#include "SpriteSheet.h"
#include "../Libraries/rapidjson/document.h"
SpriteSheet::SpriteSheet()
{
    const char* jsonString = fw::LoadCompleteFile("Data/Textures/Sprites.json", nullptr);
    rapidjson::Document document;
    document.Parse(jsonString);
    delete[] jsonString;

    rapidjson::Value& spriteToolVersion = document["SpriteTool"];
    int version = spriteToolVersion.GetInt();

    int width = document["Width"].GetInt();
    int height = document["Height"].GetInt();

    rapidjson::Value& spriteArray = document["Sprites"];
    for (rapidjson::SizeType i = 0; i < spriteArray.Size(); i++)
    {
        rapidjson::Value& sprite = spriteArray[i];
        int x = sprite["X"].GetInt();
        int y = sprite["Y"].GetInt();
        std::string name = sprite["Name"].GetString();
        int w = sprite["W"].GetInt();
        int h = sprite["H"].GetInt();
        
        SpriteInfo* s = new SpriteInfo(name,fw::vec2(w/width,h/height),fw::vec2(x/width,y/height));
        m_SpriteList.push_back(s);
    }

    int bp = 1;
}

SpriteSheet::~SpriteSheet()
{
}

SpriteInfo* SpriteSheet::GetSpriteInfo(std::string name)
{
    for (int i = 0; i < m_SpriteList.size(); i++) {
        if (m_SpriteList[i]->name == name) {
            return m_SpriteList[i];
        }
    }
    return nullptr;
}
