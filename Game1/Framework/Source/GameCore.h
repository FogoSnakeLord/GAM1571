#pragma once

namespace fw {

class GameCore
{
public:
    virtual ~GameCore() = 0 {}

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
};

} // namespace fw
