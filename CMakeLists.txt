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
# ImPlot -Quellcode direkt ins Projekt einfügen
set(IMPLOT_DIR externals/implot)
set(IMPLOT_SOURCES
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
)
# Libusb includ dircetory
set(LIBUSB_INCLUDE_DIRS /usr/include/libusb-1.0)

# GLFW hinzufügen
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
# libusb hinzufügen
find_package(PkgConfig REQUIRED)
#pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp ${IMGUI_SOURCES} ${IMPLOT_SOURCES})

# Add subdirectory for imgui and implot
target_include_directories(${PROJECT_NAME} 
    # add imgui directory
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
    # add implot directory
    PUBLIC ${IMPLOT_DIR}
    PUBLIC ${IMPLOT_DIR}/backends
    # add libusb directory
    PUBLIC ${LIBUSB_INCLUDE_DIRS}
)

# Bibliotheken
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL libusb-1.0.a)

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