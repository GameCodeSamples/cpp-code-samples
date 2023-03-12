#include <iostream>
#include <vector>
#include "app.hpp"


// const int FPS = 60;
// const int MS_PER_FRAME = 1000 / FPS;

// static void glfw_error_callback(int error, const char *description)
// {
//     fprintf(stderr, "Glfw Error %d: %s\n", error, description);
// }

// // Simple helper function to load an image into a OpenGL texture with common settings
// void LoadTextureFromOpenCV(cv::Mat img, GLuint *out_texture)
// {
//     cv::Size size = img.size();
//     unsigned char *image_data = img.data;
//     bool created = false;

//     if (!*out_texture)
//     {
//         glGenTextures(1, out_texture);
//         created = true;
//     }

//     // Create a OpenGL texture identifier
//     glBindTexture(GL_TEXTURE_2D, *out_texture);

//     // Setup filtering parameters for display
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

//     // Upload pixels into texture
// #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
//     glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
// #endif
//     if (created)
//     {
//         glTexImage2D(GL_TEXTURE_2D,
//             

// const int FPS = 60;
// const int MS_PER_FRAME = 1000 / FPS;

// static void glfw_error_callback(int error, const char *description)
// {
//     fprintf(stderr, "Glfw Error %d: %s\n", error, description);
// }

// // Simple helper function to load an image into a OpenGL texture with common settings
// void LoadTextureFromOpenCV(cv::Mat img, GLuint *out_texture)
// {
//     cv::Size size = img.size();
//     unsigned char *image_data = img.data;
//     bool created = false;

//     if (!*out_texture)
//     {
//         glGenTextures(1, out_texture);
//         created = true;
//     }

//     // Create a OpenGL texture identifier
//     glBindTexture(GL_TEXTURE_2D, *out_texture);

//     // Setup filtering parameters for display
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

//     // Upload pixels into texture
// #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
//     glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
// #endif
//     if (created)
//     {
//         glTexImage2D(GL_TEXTURE_2D,
//                      0,
//                      GL_RGB,
//                      size.width,
//                      size.height,
//                      0,
//                      GL_BGR,
//                      GL_UNSIGNED_BYTE,
//                      image_data);
//     }
//     else
//     {
//         glTexSubImage2D(GL_TEXTURE_2D,
//                         0,
//                         0,
//                         0,
//                         size.width,
//                         size.height,
//                         GL_BGR,
//                         GL_UNSIGNED_BYTE,
//                         image_data);
//     }
// }

// cv::Mat original;
// cv::Mat displayImage;
// int my_image_width = 0;
// int my_image_height = 0;
// GLuint my_image_texture = 0;
// std::vector<cv::Rect> rects;
// int ksize = 2;

// void UpdateTexture()
// {
//     LoadTextureFromOpenCV(displayImage, &my_image_texture);
// }

// void Crop(cv::Mat &img)
// {
//     cv::Mat gray, thresh, close, dilate;

//     cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);
//     cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY_INV + cv::THRESH_OTSU);
//     auto kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(ksize, ksize));
//     cv::morphologyEx(thresh, close, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 2);
//     cv::dilate(close, dilate, kernel);

//     std::vector<std::vector<cv::Point>> contours;
//     cv::findContours(dilate, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

//     rects.clear();
//     rects.reserve(contours.size());

//     for (auto &&c : contours)
//     {
//         cv::Rect rect = cv::boundingRect(c);
//         rects.emplace_back(rect);
//         cv::rectangle(img, rect, cv::Scalar(0, 0, 255), 2);
//     }

//     UpdateTexture();
// }         GL_BGR,
//                      GL_UNSIGNED_BYTE,
//                      image_data);
//     }
//     else
//     {
//         glTexSubImage2D(GL_TEXTURE_2D,
//                         0,
//                         0,
//                         0,
//                         size.width,
//                         size.height,
//                         GL_BGR,
//                         GL_UNSIGNED_BYTE,
//                         image_data);
//     }
// }

// cv::Mat original;
// cv::Mat displayImage;
// int my_image_width = 0;
// int my_image_height = 0;
// GLuint my_image_texture = 0;
// std::vector<cv::Rect> rects;
// int ksize = 2;

// void UpdateTexture()
// {
//     LoadTextureFromOpenCV(displayImage, &my_image_texture);
// }

// void Crop(cv::Mat &img)
// {
//     cv::Mat gray, thresh, close, dilate;

//     cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);
//     cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY_INV + cv::THRESH_OTSU);
//     auto kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(ksize, ksize));
//     cv::morphologyEx(thresh, close, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 2);
//     cv::dilate(close, dilate, kernel);

//     std::vector<std::vector<cv::Point>> contours;
//     cv::findContours(dilate, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

//     rects.clear();
//     rects.reserve(contours.size());

//     for (auto &&c : contours)
//     {
//         cv::Rect rect = cv::boundingRect(c);
//         rects.emplace_back(rect);
//         cv::rectangle(img, rect, cv::Scalar(0, 0, 255), 2);
//     }

//     UpdateTexture();
// }

int main(int argv, char **args)
{

    App app;
    if (app.init("Tool"))
    {
        return -1;
    }
    app.run();

    // GLFWwindow *window;

    // // GLFW
    // glfwSetErrorCallback(glfw_error_callback);
    // if (!glfwInit())
    // {
    //     std::cout << "error initializing glfw" << std::endl;
    //     return -1;
    // }

    // window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);

    // const char *glsl_version = "#version 130";
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwMaximizeWindow(window);
    // glfwSwapInterval(1); // Enable vsync

    // glfwMakeContextCurrent(window);

	// GLenum err = glewInit();
	// if (GLEW_OK != err)
	// {
	// 	std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	// 	glfwTerminate();
	// 	return -1;
	// }

    // // Setup Dear ImGui context
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO &io = ImGui::GetIO();
    // //(void)io;
    // // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // //  Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    // // ImGui::StyleColorsLight();
    // //  Setup Platform/Renderer backends
    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init(glsl_version);

    // // app state
    // bool show_another_window = false;
    // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // // load image
    // // bool ret = LoadTextureFromFile("assets/img.jpg", &my_image_texture, &my_image_width, &my_image_height);

    // original = cv::imread("assets/test4.png", cv::IMREAD_COLOR);
    // original.copyTo(displayImage);
    // my_image_width = displayImage.cols;
    // my_image_height = displayImage.rows;
    // LoadTextureFromOpenCV(displayImage, &my_image_texture);

    // while (!glfwWindowShouldClose(window))
    // {
    //     // handle input
    //     glfwPollEvents();

    //     // Start the Dear ImGui frame
    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui_ImplGlfw_NewFrame();
    //     ImGui::NewFrame();

    //     // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    //     {
    //         ImGui::Begin("Tools");
    //         ImGui::Text("Automatic crop");
    //         ImGui::InputInt("Ksize", &ksize, 1);

    //         if (ImGui::Button("Crop")) // Buttons return true when clicked (most widgets return true when edited/activated)
    //         {
    //             original.copyTo(displayImage);
    //             Crop(displayImage);
    //         }

    //         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //         ImGui::End();
    //     }

    //     {
    //         if (rects.size() > 0)
    //         {

    //             ImGui::Begin("Rects info");
    //             for (auto &&r : rects)
    //             {
    //                 ImGui::Text("X: %d, Y: %d, Width: %d, Height: %d", r.x, r.y, r.width, r.height);
    //             }
    //             ImGui::End();
    //         }
    //     }

    //     {
    //         ImGui::Begin("OpenGL Texture Text");
    //         // ImGui::Text("pointer = %p", my_image_texture);
    //         ImGui::Text("size = %d x %d", my_image_width, my_image_height);
    //         ImGui::Image((void *)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));

    //         // ImDrawList *drawList = ImGui::GetWindowDrawList();
    //         // auto color = ImColor(ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
    //         // for (auto &&r : rects)
    //         // {
    //         //     drawList->AddRect(ImVec2(r.x, r.y), ImVec2(r.x + r.width, r.y + r.height), color, 0, 0, 3);
    //         // }

    //         ImGui::End();
    //     }

    //     // Render
    //     ImGui::Render();
    //     int display_w, display_h;

    //     glfwGetFramebufferSize(window, &display_w, &display_h);
    //     glViewport(0, 0, display_w, display_h);
    //     glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //     glfwSwapBuffers(window);
    // }

    // // Cleanup
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();

    // glfwDestroyWindow(window);
    // glfwTerminate();

    return 0;
}