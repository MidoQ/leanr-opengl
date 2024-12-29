cmake_minimum_required(VERSION 3.5.0)
project(learn_opengl VERSION 0.1.0 LANGUAGES C CXX)

# file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib-mingw-w64)

# add_executable(learn_opengl src/main.cpp)
# target_link_libraries(learn_opengl libglfw3.a)

# add_executable(hello_window src/hello_window.cpp src/glad.c)
# target_link_libraries(hello_window libglfw3.a)

# add_executable(hello_triangle src/hello_triangle.cpp src/glad.c)
# target_link_libraries(hello_triangle libglfw3.a)

# add_executable(hello_rectangle src/hello_rectangle.cpp src/glad.c)
# target_link_libraries(hello_rectangle libglfw3.a)

add_executable(load_texture src/load_texture.cpp src/glad.c src/stb_image.cpp src/shader_s.cpp)
target_link_libraries(load_texture libglfw3.a)
