#pragma once

namespace fw {

class ShaderProgram;

class Mesh
{
public:
    Mesh(int numVerts, std::vector<float> vertices);
    virtual ~Mesh();

    void Draw(fw::ShaderProgram* pShader);

protected:
    GLuint m_VBO;
};

} // namespace fw
