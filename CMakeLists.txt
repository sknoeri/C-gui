cmake_minimum_required(VERSION 3.13.4)

# Set the project name
project(CppGuiProject)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)
# Add subdirectory for GLFW

add_library(imgui STATIC
    externals/imgui/imgui.cpp
    externals/imgui/imgui_draw.cpp
    externals/imgui/imgui_demo.cpp
    externals/imgui/imgui_tables.cpp
    externals/imgui/backends/imgui_impl_glfw.cpp
    externals/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC externals/imgui externals/imgui/backends)
target_link_libraries(imgui PRIVATE glfw GL)

# Add the include directory for GLFW
target_include_directories(${PROJECT_NAME} 
    PUBLIC externals/glfw/include
)
# Link directories for GLFW
target_link_directories(${PROJECT_NAME}
    PUBLIC out/build/externals/glfw/deps
)

# Link the GLFW library
target_link_libraries(${PROJECT_NAME} 
    PUBLIC glfw
)