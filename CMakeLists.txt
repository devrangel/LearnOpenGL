cmake_minimum_required(VERSION 3.12)

project("LearnOpenGL")

add_executable(LearnOpenGL "src/main.cpp" "src/utils/callbacks.cpp"  "src/geometries/triangle.cpp")

target_include_directories(LearnOpenGL PRIVATE deps/include)

target_link_directories(LearnOpenGL PRIVATE deps/lib)
target_link_libraries(LearnOpenGL PRIVATE glfw3.lib
										  glew32.lib
										  opengl32.lib)

add_custom_command(TARGET LearnOpenGL POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/lib/glew32.dll" "${CMAKE_BINARY_DIR}/glew32.dll")
