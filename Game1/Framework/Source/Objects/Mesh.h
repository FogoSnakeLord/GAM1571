#pragma once

namespace fw {

class ShaderProgram;

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();

    void Draw(fw::ShaderProgram* pShader);

protected:
    GLuint m_VBO;
};

} // namespace fw
