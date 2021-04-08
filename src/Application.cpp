#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Specify openGL version to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960.0f, 540.0f, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Match framerate to monitor
    glfwSwapInterval(1);

    // Make Glew context after valid glfw context
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;



    std::cout << glGetString(GL_VERSION) << std::endl;
    // Scope to trigger the stack destructors of buffers classes before glfw context is deleted
    {
        //// Vertex positions
        //float positions[] = {
        //    -50.0f, -50.0f, 0.0f, 0.0f, // 0
        //     50.0f, -50.0f, 1.0f, 0.0f, // 1
        //     50.0f,  50.0f, 1.0f, 1.0f, // 2
        //    -50.0f,  50.0f, 0.0f, 1.0f  // 3
        //};

        //// Setup Index Buffer to reduce repeated positions for vertices
        //unsigned int indices[] = {
        //    0, 1, 2, // bottom-right triangle
        //    2, 3, 0  // bottom-left triangle
        //};

        // Setup Blending, disabled by default
        GLCall(glEnable(GL_BLEND));
        // define source and destination for blending
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //// Buffers send data to the GPU
        //VertexArray va;
        //VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        //// Enable and describe vertex attributes. This is done on the vao
        //// Each vertex position is 2 floats long, so we mark this in the layout
        //VertexBufferLayout layout;
        //layout.Push<float>(2);
        //layout.Push<float>(2);
        //va.AddBuffer(vb, layout);

        //// index buffers *must* be unsigned ints
        //IndexBuffer ib(indices, 6);

        //// defining projection boundaries
        //glm::mat4 proj = glm::ortho(
        //    0.0f, 960.0f, // x
        //    0.0f, 540.0f, // y
        //    -1.0f, 1.0f   // z
        //);
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        //Shader shader("res/shaders/Basic.shader");
        //shader.Bind();
        //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        //Texture texture("res/textures/transparentbg.png");
        //// Texture is bound to slot 0 by default
        //texture.Bind();
        //shader.SetUniform1i("u_Texture", 0);

        //// unbind test
        //va.Unbind();
        //ib.Unbind();
        //vb.Unbind();
        //shader.Unbind();

        Renderer renderer;

            // Setup ImGUI
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGui::GetStyle().WindowRounding = 5.0f;
        ImGui_ImplOpenGL3_Init((char*) glGetString(330));

        //glm::vec3 translationA(200, 200, 0);
        //glm::vec3 translationB(400, 400, 0);

        //float r = 0.0f;
        //float increment = 0.01f;

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            /* Render here */
            renderer.Clear();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            //{
            //    // matrix multiplication, order matters
            //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            //    glm::mat4 mvp = proj * view * model;
            //    shader.Bind();

            //    shader.SetUniformMat4f("u_MVP", mvp);
            //    renderer.Draw(va, ib, shader);
            //}

            //{
            //    // matrix multiplication, order matters
            //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            //    glm::mat4 mvp = proj * view * model;

            //    shader.SetUniformMat4f("u_MVP", mvp);
            //    renderer.Draw(va, ib, shader);
            //}

            //// Animating red channel per frame
            //if (r > 1.0f) { increment = -0.01f; }
            //else if (r < 0.0f) { increment = 0.01f; }

            //r += increment;

            //// ImGui Example Window
            //{
            //    static float f = 0.0f;

            //    ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 800.0f);
            //    ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 800.0f);
            //    ImGui::Text(
            //        "Application average %.3f ms/frame (%.1f FPS)", 
            //        1000.0f / ImGui::GetIO().Framerate, 
            //        ImGui::GetIO().Framerate
            //    );
            //}

            // ImGui Render
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        if (currentTest != testMenu) { delete testMenu; }
        delete currentTest;
    }
    // ImGui Shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}  