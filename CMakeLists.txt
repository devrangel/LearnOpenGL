cmake_minimum_required(VERSION 3.12)

project("LearnOpenGL")

add_executable(LearnOpenGL "src/main.cpp" 
						   "src/geometries/triangle.cpp" 
						   "src/geometries/rectangle.cpp" 
						   "src/utils/shader.cpp" 
						   "src/geometries/rectangle_texture.cpp")

target_include_directories(LearnOpenGL PRIVATE deps/include
											   src)

target_link_directories(LearnOpenGL PRIVATE deps/lib)
target_link_libraries(LearnOpenGL PRIVATE glfw3.lib
										  glew32.lib
										  opengl32.lib)

add_custom_command(TARGET LearnOpenGL POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/lib/glew32.dll" "${CMAKE_BINARY_DIR}/glew32.dll")
add_custom_command(TARGET LearnOpenGL POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/assets/stone.jpg" "${CMAKE_BINARY_DIR}/assets/stone.jpg")
add_custom_command(TARGET LearnOpenGL POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/assets/face.png" "${CMAKE_BINARY_DIR}/assets/face.png")
