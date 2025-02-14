cmake_minimum_required(VERSION 3.13.4)

# Set the project name
project(CppGuiProject)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)
# Add subdirectory for GLFW
add_subdirectory(externals/glfw)
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