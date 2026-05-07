add_library(glad STATIC 
    src/glad.c
)

target_include_directories(glad PUBLIC include)

# Pour éviter des problèmes sur Linux/Unix avec les threads
find_package(Threads REQUIRED)
target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS} Threads::Threads)
