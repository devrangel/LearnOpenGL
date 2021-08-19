#pragma once

#include "camera.h"

class IGeometry
{
public:
	virtual void draw(const Camera& camera) = 0;
};