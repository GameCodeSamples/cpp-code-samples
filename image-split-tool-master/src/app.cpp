#include "app.hpp"

#include <iostream>
#include <bitset>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Core/renderer.hpp"

#include "UI/state.hpp"
#include "UI/image.hpp"
#include "UI/menu.hpp"
#include "UI/crop.hpp"
#include "UI/concat.hpp"

UI::AppState appState;
UI::ManualCropState manualCropState;
UI::AutomaticCropState autoCropState;
UI::ImageState cropState;

void initImGui(GLFWwindow *window, const char *glslVersion)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    //(void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //  Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    //  Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);
}

App::App() {}

App::~App() {}

int App::init(const char *title)
{
    const char *glslVersion = "#version 130";
    if (Renderer::init(title, glslVersion, window))
    {
        return -1;
    }
    initImGui(window, glslVersion);
    return 0;
}

void App::run()
{
    while (!glfwWindowShouldClose(window))
    {
        // handle input
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        UI::menu(appState);

        if (appState.active == UI::CROP)
        {
            /* code */
        }

        switch (appState.active)
        {
        case UI::CROP:
            UI::cropWindow(cropState, autoCropState, manualCropState);
            break;
        case UI::CONCAT:
            /* code */
            break;
        default:
            break;
        }

        // Render
        ImGui::Render();
        Renderer::render(window);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        Renderer::swapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    Renderer::clear(window);

    delete cropState.imagePath;
}
