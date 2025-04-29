#include <iostream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
// #include <libusb.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}
// void list_usb_devices()
// {
//     // variables for lib usb
//     libusb_context *ctx = nullptr;
//     libusb_device **devs = nullptr;
//     ssize_t cnt;
//     // Initialize libusb
//     int r = libusb_init(&ctx);
//     if (r < 0) {
//         std::cerr << "Failed to initialize libusb: " << libusb_error_name(r) << std::endl;
//     }
//     // Get the list of USB devices
//     cnt = libusb_get_device_list(ctx, &devs);
//     if (cnt < 0) {
//         std::cerr << "Failed to get USB device list: " << libusb_error_name(cnt) << std::endl;
//         libusb_exit(ctx);
//     }

//     std::cout << "Number of USB devices found: " << cnt << std::endl;

//     // Iterate over the list of devices and print their details
//     for (ssize_t i = 0; i < cnt; ++i) {
//         libusb_device *dev = devs[i];
//         libusb_device_descriptor desc;
//         r = libusb_get_device_descriptor(dev, &desc);
//         if (r < 0) {
//             std::cerr << "Failed to get device descriptor: " << libusb_error_name(r) << std::endl;
//             continue;
//         }

//         std::cout << "Device " << i << ": "
//                   << "Vendor ID: " << std::hex << desc.idVendor
//                   << ", Product ID: " << std::hex << desc.idProduct
//                   << std::dec << std::endl;
//     }

//     // Free the list of devices
//     libusb_free_device_list(devs, 1);

//     // Deinitialize libusb
//     libusb_exit(ctx);
// }

int main() {
    // list_usb_devices(); // List USB devices
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
    ImPlot::CreateContext();  // ImPlot-Context initialisieren

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Beispielhafte X-Y-Daten
    std::vector<float> x_data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<float> y_data = {0.2f, 0.3f, 0.5f, 0.4f, 0.6f, 0.9f, 1.2f, 1.0f, 0.8f, 0.7f};

    std::string feedback="";
    char textBuffer[256] = "";
    // Hauptloop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // ImGui Frame starten
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // here's the ImGui window resizing code
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        ImGui::SetNextWindowSize(ImVec2(width, height)); // ensures ImGui fits the GLFW window
        ImGui::SetNextWindowPos(ImVec2(0, 0)); // ensures ImGui fits the GLFW window
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

        // Plot mit implot machen
        if (ImPlot::BeginPlot("Mein 2D-Plot", ImVec2(-1, 0), ImPlotFlags_Crosshairs)) {
            ImPlot::SetupAxes("X-Werte", "Y-Werte"); // Achsentitel setzen
            // ImPlot::SetupAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always); // Zoom-Grenzen für X
            // ImPlot::SetupAxisLimits(ImAxis_Y1, y_min, y_max, ImGuiCond_Always); // Zoom-Grenzen für Y
            ImPlot::PlotLine("Messwerte", x_data.data(), y_data.data(), x_data.size());
            ImPlot::EndPlot();
        }
        ImGui::End();
        // Rendering
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Aufräumen
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}