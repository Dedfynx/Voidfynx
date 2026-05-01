option(VF_ENABLE_LOGGING "Enable logging system" ON)
option(VF_ENABLE_ASSERTS "Enable assertion system" ON)

#Lib 
find_package(OpenGL REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
CPMAddPackage(
  NAME fmt
  GIT_TAG 12.1.0
  GITHUB_REPOSITORY fmtlib/fmt
)

CPMAddPackage(
        NAME GLFW
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.4
        OPTIONS
          "GLFW_BUILD_TESTS OFF"
          "GLFW_BUILD_EXAMPLES OFF"
          "GLFW_BUILD_DOCS OFF"
)

file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.h")

add_library(Voidfynx SHARED ${ENGINE_SOURCES})
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


target_link_libraries(Voidfynx PUBLIC fmt::fmt glfw OpenGL::GL)

