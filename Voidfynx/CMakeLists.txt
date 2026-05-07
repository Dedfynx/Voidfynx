option(VF_ENABLE_LOGGING "Enable logging system" ON)
option(VF_ENABLE_DEBUG   "Enable debug system"   ON)

#Lib 
find_package(OpenGL REQUIRED)

## {fmt}
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
CPMAddPackage(
  NAME fmt
  GIT_TAG 12.1.0
  GITHUB_REPOSITORY fmtlib/fmt
)
## GLFW
CPMAddPackage(
        NAME GLFW
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.4
        OPTIONS
          "GLFW_BUILD_TESTS OFF"
          "GLFW_BUILD_EXAMPLES OFF"
          "GLFW_BUILD_DOCS OFF"
)

## ImGui
CPMAddPackage(
  NAME imgui
  VERSION 1.91.1
  GITHUB_REPOSITORY ocornut/imgui
  DOWNLOAD_ONLY TRUE
)

# CMakeLists.txt from https://gist.githubusercontent.com/rokups/f771217b2d530d170db5cb1e08e9a8f4
file(
  DOWNLOAD
  "https://gist.githubusercontent.com/rokups/f771217b2d530d170db5cb1e08e9a8f4/raw/4c2c14374ab878ca2f45daabfed4c156468e4e27/CMakeLists.txt"
  "${imgui_SOURCE_DIR}/CMakeLists.txt"
  EXPECTED_HASH SHA256=fd62f69364ce13a4f7633a9b50ae6672c466bcc44be60c69c45c0c6e225bb086
)

# Options
set(IMGUI_EXAMPLES FALSE)
set(IMGUI_DEMO TRUE)
set(IMGUI_ENABLE_STDLIB_SUPPORT TRUE)
# FreeType (https://github.com/cpm-cmake/CPM.cmake/wiki/More-Snippets#freetype)
set(FREETYPE_FOUND TRUE)
set(FREETYPE_INCLUDE_DIRS "")
set(FREETYPE_LIBRARIES Freetype::Freetype)

# Add subdirectory
add_subdirectory(${imgui_SOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/imgui" EXCLUDE_FROM_ALL SYSTEM)

set(IMGUI_BACKENDS
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
######

##GLAD
add_subdirectory(third_party/GLAD)

#Src files
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.h")

add_library(Voidfynx SHARED ${ENGINE_SOURCES} ${IMGUI_BACKENDS})
target_include_directories(Voidfynx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers(Voidfynx PRIVATE "src/vf_pch.h")

target_compile_definitions(Voidfynx PRIVATE VF_BUILD_DLL)

#Options
if(VF_ENABLE_LOGGING)
	target_compile_definitions(Voidfynx PUBLIC VF_ENABLE_LOGGING)
endif()

if(VF_ENABLE_ASSERTS)
	target_compile_definitions(Voidfynx PUBLIC VF_ENABLE_ASSERTS)
endif()


target_link_libraries(Voidfynx PUBLIC fmt::fmt glfw OpenGL::GL glad imgui)

