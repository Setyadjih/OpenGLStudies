#pragma once
#include <vector>
#include <GL\glew.h>
#include "Renderer.h"

// Struct that defines the layout of a Vertex Attribute element
// e.g. position is 3 floats, not normalized
struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;
    }
};

// A class to hold all the different attribute types in the VertexBufferObject.
// we use this to describe all the different attribute elements sequentially
// e.g. m_Elements = {position layout, color layout, normal layout, etc...}
class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    
    // total length in bytes from one vertex to the next (total size of all attributes)
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        :m_Stride(0)
    {
    }

    template<typename T>
    void Push(unsigned int count)
    {
        static_assert(false);
    }

    template<>
    void Push<float>(unsigned int count)
    {
        m_Elements.push_back(VertexBufferElement{GL_FLOAT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }
    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back(VertexBufferElement{GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }
    
    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back(VertexBufferElement{GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
    inline unsigned int GetStride() const& { return m_Stride; }
};

