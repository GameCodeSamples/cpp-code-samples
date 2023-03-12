#pragma once

#include <imgui.h>
#include <vector>
#include "image.hpp"
#include "Actions/images.hpp"

const char* IMAGE_CHILD_IDENTIFIER = "CROP_IMAGE_ID";

namespace UI
{
    struct AutomaticCropState
    {
        std::vector<cv::Rect> rects;
        int ksize = 2;
    };

    struct ManualCropState
    {
        int rowscols[2] = {2, 5};
        int offsetX = 0;
        int offsetY = 0;
        int paddingX = 0;
        int paddingY = 0;
    };

    void manualCrop(UI::ImageState &imageState, ManualCropState &manualCropState)
    {
        ImGui::Begin("Manual grid crop");
        ImGui::Text("Manual crop");
        ImGui::Text("Rows and columns");
        ImGui::InputInt2("##Rows and columns", manualCropState.rowscols);
        ImGui::End();

        ImGui::Begin("OpenGL Texture Text");
        UI::renderImage(imageState, IMAGE_CHILD_IDENTIFIER);

        // draw rects on image
        if (imageState.imagePath)
        {
            ImGui::BeginChild(IMAGE_CHILD_IDENTIFIER);
            ImDrawList *drawList = ImGui::GetWindowDrawList();
            if (manualCropState.rowscols[0] > 0 && manualCropState.rowscols[1] > 0)
            {
                int rectHeight = static_cast<int>(imageState.imageHeight / manualCropState.rowscols[0]);
                int rectWidth = static_cast<int>(imageState.imageWidth / manualCropState.rowscols[1]);
                auto color = ImColor(ImVec4(0.0f, 0.0f, 1.0f, 1.0f));

                for (int i = 0; i < manualCropState.rowscols[0]; i++)
                {
                    int startY = rectHeight * i;
                    for (int j = 0; j < manualCropState.rowscols[1]; j++)
                    {
                        int startX = rectWidth * j;
                        drawList->AddRect(
                            ImVec2(startX + imageState.imageGlobalPos.x, startY + imageState.imageGlobalPos.y),
                            ImVec2(startX + rectWidth + imageState.imageGlobalPos.x, startY + rectHeight + imageState.imageGlobalPos.y), color, 0, 0, 0.1f);
                    }
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }

    void automaticCrop(UI::ImageState &imageState, UI::AutomaticCropState &autoCropState)
    {
        ImGui::Begin("Automatic crop");
        ImGui::InputInt("Ksize", &autoCropState.ksize, 1);

        if (ImGui::Button("Automatic Crop")) // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            imageState.original.copyTo(imageState.displayImage);
            Actions::Images::Crop(imageState.displayImage, autoCropState.ksize, autoCropState.rects);
            Renderer::UpdateTexture(imageState.textureId, imageState.displayImage.data, imageState.displayImage.cols, imageState.displayImage.rows);
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        if (autoCropState.rects.size() > 0)
        {
            ImGui::Begin("Rects info");
            // char buff[100];
            std::stringstream stream;
            uint32_t idx = 0;
            for (auto &&r : autoCropState.rects)
            {
                stream << idx << " (" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << ")" << std::endl;
                ImGui::Text("X: %d, Y: %d, Width: %d, Height: %d", r.x, r.y, r.width, r.height);
                idx++;
            }
            ImGui::NewLine();
            auto text = stream.str();
            ImGui::InputTextMultiline("C++ export", text.data(), text.length());
            ImGui::End();
        }
        ImGui::End();
    }

    void cropWindow(UI::ImageState &imageState, AutomaticCropState &autoCropState, ManualCropState &manualCropState)
    {
        automaticCrop(imageState, autoCropState);
        manualCrop(imageState, manualCropState);
    }
}