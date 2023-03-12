#pragma once

#include <imgui.h>
#include "state.hpp"

namespace UI
{
    void menu(UI::AppState &appState)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("Crop"))
                {
                    appState.active = UI::CROP;
                }

                if (ImGui::MenuItem("Concat"))
                {
                    appState.active = UI::CONCAT;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
} // namespace UI