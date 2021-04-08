#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// Macros to help debug. 
// Creates a breakpoint in code when glGetError != GL_NO_ERROR
#define ASSERT(x) if (!(x)) __debugbreak();

// Wrap function with logging faculties. Clear log before calling. 
// If an error is produced, log to console
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Get all errors until fully cleared
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};