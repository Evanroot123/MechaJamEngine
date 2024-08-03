#include "camera.hpp"

Camera::Camera()
{
	pos.x = 0;
	pos.y = 0;
}

void Camera::pan(double x, double y)
{
	pos.x += x * zoomLevel;
	pos.y -= y * zoomLevel;
}

void Camera::zoom(double zoom)
{
	zoomLevel += zoom > 0 ? -0.1 : 0.1;
	if (zoomLevel < maxZoomIn)
		zoomLevel = maxZoomIn;
	if (zoomLevel > maxZoomOut)
		zoomLevel = maxZoomOut;
}

void Camera::resetZoom()
{
	zoomLevel = standardZoom;
}
