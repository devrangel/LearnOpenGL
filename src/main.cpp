#include <iostream>
#include <cassert>

#include "application.h"
#include "scene.h"
#include "camera.h"
//#include "geometries/triangle.h"
//#include "geometries/rectangle.h"
//#include "geometries/rectangle_texture.h"
#include "geometries/cube.h"

int main()
{
	const int WIDTH_SCREEN = 800;
	const int HEIGHT_SCREEN = 600;

	Application app(WIDTH_SCREEN, HEIGHT_SCREEN, "LearnOpenGL");

	Cube cube("assets/stone.jpg", "assets/face.png");
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Scene scene(cube, camera, WIDTH_SCREEN, HEIGHT_SCREEN);

	app.run(scene);

	return 0;
}


