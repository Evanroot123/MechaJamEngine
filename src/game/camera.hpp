#pragma once

#include "glm.hpp"

class Camera
{
public:
	glm::vec2 pos;
	float zoomLevel = 1.0f;
	float maxZoomIn = 0.1f;
	float maxZoomOut = 3.0f;
	float standardZoom = 1.0f;

	Camera();
	void pan(double x, double y);
	void zoom(double zoom);
	void resetZoom();
};