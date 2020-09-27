cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(TinyEngine)

file(GLOB_RECURSE SRCS ../engine/*.cpp)
add_executable(TinyEngine ${SRCS})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

include_directories(/usr/local/Cellar/glm/0.9.9.8/include)
include_directories(/usr/local/Cellar/glew/2.1.0_1/include)

target_link_libraries(TinyEngine ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} /usr/local/Cellar/glew/2.1.0_1/lib/libGlew.dylib)

install(TARGETS TinyEngine RUNTIME DESTINATION bin)