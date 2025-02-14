cmake_minimum_required(VERSION 3.13.4)

# Set the project name
project(CppGuiProject)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)
# Add subdirectory for GLFW
add_subdirectory(external/glfw)