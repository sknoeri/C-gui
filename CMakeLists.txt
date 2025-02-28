cmake_minimum_required(VERSION 3.13.4)

# Set the project name
project(CppGuiProject)

# ImGui-Quellcode direkt ins Projekt einfügen
set(IMGUI_DIR externals/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# GLFW hinzufügen
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp ${IMGUI_SOURCES})

# Add subdirectory for imgui
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
)

# Bibliotheken
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)

# add_library(imgui STATIC
#     externals/imgui/imgui.cpp
#     externals/imgui/imgui_draw.cpp
#     externals/imgui/imgui_demo.cpp
#     externals/imgui/imgui_tables.cpp
# )

# target_include_directories(imgui PUBLIC externals/imgui externals/imgui/backends)
# target_link_libraries(imgui PRIVATE glfw GL)

# # Add the include directory for GLFW

# # Link directories for GLFW
# target_link_directories(${PROJECT_NAME}
#     PUBLIC out/build/externals/glfw/deps
# )

# # Link the GLFW library
# target_link_libraries(${PROJECT_NAME} 
#     PUBLIC glfw
# )