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
# # Set the include directory for libusb
set(LIBUSB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libraries/libusb/include/libusb-1.0)

# # Set the library directory for libusb
set(LIBUSB_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/libusb/lib)   


# libusb suchen
find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# OpenGL hinzufügen
find_package(OpenGL REQUIRED)

# Add subdirectory for glfw
add_subdirectory(externals/glfw glfw)

# # Libusb als statische Bibliothek erstellen
# add_library(libusb STATIC ${LIBUSB_SOURCES})

# Add the executable
add_executable(${PROJECT_NAME} main.cpp ${IMGUI_SOURCES} ${IMPLOT_SOURCES})

# Add subdirectory for imgui and implot
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_SOURCE_DIR}/inc
    # add imgui directory
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
    # add implot directory
    PUBLIC ${IMPLOT_DIR}
    PUBLIC ${IMPLOT_DIR}/backends
    PUBLIC ${LIBUSB_INCLUDE_DIR}
)

# Bibliotheken
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL 
    ${LIBUSB_LIB_DIR}/libusb-1.0.a
    udev
    # ${LIBUSB_LIBRARIES}
)