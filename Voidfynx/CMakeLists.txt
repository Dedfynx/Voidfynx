option(VF_ENABLE_LOGGING "Enable logging system" ON)

#Lib 
find_package(fmt REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.h")


add_library(Voidfynx SHARED ${ENGINE_SOURCES})
target_include_directories(Voidfynx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers(Voidfynx PRIVATE "src/vxpch.h")

target_compile_definitions(Voidfynx PRIVATE VF_BUILD_DLL)
if(VF_ENABLE_LOGGING)
	target_compile_definitions(Voidfynx PUBLIC VF_ENABLE_LOGGING)
endif()

target_link_libraries(Voidfynx PUBLIC fmt::fmt)

