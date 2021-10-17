#include "CoreHeaders.h"

#include "Mesh.h"
#include "ShaderProgram.h"

namespace fw {

Mesh::Mesh(int numVerts, std::vector<float> vertices)
    : m_VBO( 0 )
{
    const int numAttributeComponentsPerVertex = 3; // x, y & a for each vertex.

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

    // Draw the primitive.
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}

} // namespace fw
