cmake_minimum_required(VERSION 3.16)

project(rclone-browser
    VERSION 2.0.0
    DESCRIPTION "Cross-platform GUI for rclone"
    LANGUAGES CXX
)

# Modern CMake settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable AUTOMOC, AUTOUIC, AUTORCC for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include current directory for generated files
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Export compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Try to find Qt6 first, fall back to Qt5
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
)

message(STATUS "Using Qt version: ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}")

# Platform-specific Qt components
if(WIN32)
    if(QT_VERSION_MAJOR EQUAL 5)
        find_package(Qt5 COMPONENTS WinExtras)
        if(Qt5WinExtras_FOUND)
            set(HAVE_QT_WINEXTRAS TRUE)
        endif()
    endif()
elseif(APPLE)
    if(QT_VERSION_MAJOR EQUAL 5)
        find_package(Qt5 COMPONENTS MacExtras)
        if(Qt5MacExtras_FOUND)
            set(HAVE_QT_MACEXTRAS TRUE)
        endif()
    endif()
    find_library(COCOA_LIB Cocoa REQUIRED)
endif()

# Version information
file(READ "VERSION" RCLONE_BROWSER_VERSION)
string(STRIP "${RCLONE_BROWSER_VERSION}" RCLONE_BROWSER_VERSION)

# Compile definitions
add_compile_definitions(RCLONE_BROWSER_VERSION="${RCLONE_BROWSER_VERSION}")
add_compile_definitions(QT_VERSION_MAJOR=${QT_VERSION_MAJOR})

if(HAVE_QT_WINEXTRAS)
    add_compile_definitions(HAVE_QT_WINEXTRAS)
endif()

if(HAVE_QT_MACEXTRAS)
    add_compile_definitions(HAVE_QT_MACEXTRAS)
endif()

# Platform-specific settings
if(WIN32)
    # Link automatically to qtmain.lib on Windows
    if(POLICY CMP0020)
        cmake_policy(SET CMP0020 NEW)
    endif()
    
    add_compile_definitions(_UNICODE UNICODE _SCL_SECURE_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE)
    
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W4")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    endif()
else()
    # GCC/Clang flags
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-Werror)
    endif()
endif()

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14" CACHE STRING "Minimum macOS version")
endif()

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

add_subdirectory(src)
