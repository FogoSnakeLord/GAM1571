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

    rapidjson::Value& sWidth = document["Width"];
    float width = sWidth.GetInt();
    rapidjson::Value& sHeight = document["Height"];
    float height = sHeight.GetInt();

    rapidjson::Value& spriteArray = document["Sprites"];
    for (rapidjson::SizeType i = 0; i < spriteArray.Size(); i++)
    {
        rapidjson::Value& sprite = spriteArray[i];
        std::string name = sprite["Name"].GetString();
        float x = sprite["X"].GetFloat();
        float y = sprite["Y"].GetFloat();
        float w = sprite["W"].GetFloat();
        float h = sprite["H"].GetFloat();
        SpriteInfo* s = new SpriteInfo(name,fw::vec2(w/width,h/height),fw::vec2(x/width,y/height));
        m_SpriteList.push_back(s);
    }
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
