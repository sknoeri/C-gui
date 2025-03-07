#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

int main() {
    // GLFW initialisieren
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cerr << "GLFW konnte nicht initialisiert werden!" << std::endl;
        return -1;
    }

    // OpenGL Kontext setzen
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Button Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Fenster konnte nicht erstellt werden!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ImGui initialisieren
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    std::string feedback="";
    char textBuffer[256] = "";
    // Hauptloop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // ImGui Frame starten
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // GUI zeichnen
        ImGui::Begin("Hello World App");
        if (ImGui::Button("Say Hello", ImVec2(200, 50))) {
            std::cout << "Hello, World!" << std::endl;
            feedback = "Hello, World!\nMulti line message\n";
            strncpy(textBuffer, feedback.c_str(), sizeof(textBuffer)); // Copy std::string to char array
            textBuffer[sizeof(textBuffer) - 1] = '\0'; // Ensure null-termination
        }

        // Textbox anzeigen
        ImGui::InputTextMultiline("##FeedbackBox", textBuffer, sizeof(textBuffer), ImVec2(400, 100)); // ImGuiInputTextFlags_ReadOnly
        ImGui::End();

        // Rendering
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Aufräumen
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}