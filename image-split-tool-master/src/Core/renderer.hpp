#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace Renderer
{
    int init(const char *windowTitle, const char *glslVersion, GLFWwindow *&window)
    {
        // GLFW
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
        {
            std::cout << "error initializing glfw" << std::endl;
            return -1;
        }

        window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwMaximizeWindow(window);
        glfwSwapInterval(1); // Enable vsync

        glfwMakeContextCurrent(window);

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
            glfwTerminate();
            return -1;
        }

        return 0;
    }

    inline void render(GLFWwindow *window)
    {
        // Render
        int display_w, display_h; // TODO pincho...
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    inline void swapBuffers(GLFWwindow *window)
    {
        glfwSwapBuffers(window);
    }

    inline uint32_t LoadTexture(unsigned char *data, uint32_t width, uint32_t height)
    {
        GLuint texture;
        glGenTextures(1, &texture); // one texture

        // Bind texture. OpenGL works as state machine.
        // All operations affect to the current binding.
        glBindTexture(GL_TEXTURE_2D, texture);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

        // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB,
                     width,
                     height,
                     0,
                     GL_BGR,
                     GL_UNSIGNED_BYTE,
                     data);

        return texture;
    }

    inline void UpdateTexture(uint32_t texture, unsigned char *data, uint32_t width, uint32_t height)
    {
        // Bind texture. OpenGL works as state machine.
        // All operations affect to the current binding.
        glBindTexture(GL_TEXTURE_2D, texture);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

        // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
        glTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        0,
                        0,
                        width,
                        height,
                        GL_BGR,
                        GL_UNSIGNED_BYTE,
                        data);
    }

    void clear(GLFWwindow *window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

} // namespace Renderer
