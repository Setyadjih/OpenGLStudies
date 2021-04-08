#pragma once

#include "VertexBuffer.h"

// Forward Declare to avoid cyclical includes
class VertexBufferLayout;

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;
};

