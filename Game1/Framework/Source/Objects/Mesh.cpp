#include "CoreHeaders.h"

#include "Mesh.h"
#include "ShaderProgram.h"
/*attribute float a_Red;
attribute float a_Green;
attribute float a_Blue;*/
namespace fw {

    Mesh::Mesh(int numVerts, std::vector<float> vertices)
        : m_VBO(0)
        , m_NumVerts(numVerts)
{
    const int numAttributeComponentsPerVertex = 3; // x, y ,r g, b & a for each vertex.

    // Generate a buffer for our vertex attributes.
    glGenBuffers( 1, &m_VBO ); // m_VBO is a GLuint.

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Copy our attribute data into the VBO.
    glBufferData( GL_ARRAY_BUFFER, sizeof(float)*numAttributeComponentsPerVertex*numVerts, &vertices[0], GL_STATIC_DRAW );

}

Mesh::~Mesh()
{
    // Release the memory.
    glDeleteBuffers( 1, &m_VBO );
}

void Mesh::Draw(fw::ShaderProgram* pShader)
{
    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Get the attribute variable’s location from the shader.
    // Describe the attributes in the VBO to OpenGL.
    GLint a_Position = glGetAttribLocation( pShader->GetProgram(), "a_Position" );
    if( a_Position != -1 )
    {
        glEnableVertexAttribArray( a_Position );
        glVertexAttribPointer( a_Position, 2, GL_FLOAT, GL_FALSE, 12, (void*)0 );
    }

    GLint a_Alpha = glGetAttribLocation( pShader->GetProgram(), "a_Alpha" );
    if( a_Alpha != -1 )
    {
        glEnableVertexAttribArray( a_Alpha );
        glVertexAttribPointer( a_Alpha, 1, GL_FLOAT, GL_FALSE, 12, (void*)8 );
    }
    /*
    GLint a_Red = glGetAttribLocation(pShader->GetProgram(), "a_Red");
    if (a_Red != -1)
    {
        glEnableVertexAttribArray(a_Red);
        glVertexAttribPointer(a_Red, 1, GL_FLOAT, GL_FALSE, 12, (void*)8);
    }
    GLint a_Blue = glGetAttribLocation(pShader->GetProgram(), "a_Blue");
    if (a_Blue != -1)
    {
        glEnableVertexAttribArray(a_Blue);
        glVertexAttribPointer(a_Blue, 1, GL_FLOAT, GL_FALSE, 12, (void*)8);
    }
    GLint a_Green = glGetAttribLocation(pShader->GetProgram(), "a_Green");
    if (a_Green != -1)
    {
        glEnableVertexAttribArray(a_Green);
        glVertexAttribPointer(a_Green, 1, GL_FLOAT, GL_FALSE, 12, (void*)8);
    }
    */
    // Draw the primitive.
    glDrawArrays(GL_LINES, 0, m_NumVerts);
    //glDrawArrays( GL_TRIANGLES, 0, m_NumVerts);
    /*for (int i = 0; i < (m_NumVerts / 3);i++) {
        glDrawArrays(GL_TRIANGLES, 0+(3*i), (3+(3*i)));
    }*/
}

} // namespace fw
