#pragma once

#include "GLFW/glfw3.h"

#include "geometries/geometry.h"
#include "camera.h"
#include "globals.h"

class Scene
{
public:
	Scene(IGeometry& geometry, Camera& camera, float screenWidth, float screenHeight)
		: m_Geometry(geometry), m_Camera(camera), m_ScreenWidth(screenWidth), m_ScreenHeigth(screenHeight)
	{

	}

	void draw(GLFWwindow* const window)
	{
		this->m_Camera.processKeyboard(window);
		this->m_Camera.processMouseMovement(Global::lastX, Global::lastY);
		this->m_Geometry.draw(this->m_Camera);
	}
	
private:
	Camera& m_Camera;
	IGeometry& m_Geometry;

	float m_ScreenWidth;
	float m_ScreenHeigth;
};