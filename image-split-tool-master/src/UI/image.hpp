#pragma once

#include <nfd.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Core/renderer.hpp"

namespace UI
{
    struct ImageState
    {
        cv::Mat original;
        cv::Mat displayImage;
        float imageWidth = 0;
        float imageHeight = 0;
        char *imagePath = nullptr;
        uint32_t textureId;

        ImVec2 imageGlobalPos;
    };

    void updateImage(UI::ImageState &imageState)
    {
        auto result = NFD_OpenDialog(NULL, NULL, &imageState.imagePath);
        if (result == NFD_OKAY)
        {
            if (imageState.textureId)
            {
                glDeleteTextures(1, &imageState.textureId);
            }
            imageState.original = cv::imread(imageState.imagePath, cv::IMREAD_COLOR);
            imageState.original.copyTo(imageState.displayImage);
            imageState.imageWidth = static_cast<float>(imageState.displayImage.cols);
            imageState.imageHeight = static_cast<float>(imageState.displayImage.rows);
            imageState.textureId = Renderer::LoadTexture(imageState.displayImage.data, static_cast<uint32_t>(imageState.imageWidth), static_cast<uint32_t>(imageState.imageHeight));
        }
        else if (result == NFD_CANCEL)
        {
            // puts("User pressed cancel.");
        }
        else
        {
            printf("Error: %s\n", NFD_GetError());
        }
    }

    void renderImage(ImageState &imageState, const char *imageChildIdentifier)
    {
        if (imageState.textureId)
        {
            if (ImGui::Button("Change image")) // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                UI::updateImage(imageState);
            }
            ImGui::SameLine();
            ImGui::Text("%s", imageState.imagePath);
            ImGui::Text("pointer = %d", imageState.textureId);
            ImGui::Text("size = %d x %d", static_cast<int>(imageState.imageWidth), static_cast<int>(imageState.imageHeight));

            // ImGui::BeginChildFrame(123, ImVec2(imageState.my_image_width, imageState.my_image_height));  //the purpose of this child is to give the image scroll bars for when it's too big

            ImGui::BeginChild(imageChildIdentifier, ImVec2(imageState.imageWidth, imageState.imageHeight));
            imageState.imageGlobalPos = ImGui::GetCursorScreenPos();
            ImGui::Image((void *)(intptr_t)imageState.textureId, ImVec2(imageState.imageWidth, imageState.imageHeight));
            ImGui::EndChild();
        }
        else
        {
            if (ImGui::Button("Select image")) // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                UI::updateImage(imageState);
            }
        }
    }
} // namespace UI
