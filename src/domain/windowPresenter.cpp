#include "window.h"

Window::~Window()
{

}

Window::Window(float width, float height)
  : width{width}
  , height{height}
{

}

void Window::addGeometry(geometries::Geometry *element)
{
  geometries.push_back(element);
}

