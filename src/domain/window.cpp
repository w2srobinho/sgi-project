#include "window.h"

#include <memory>

Window::~Window()
{

}

Window::Window(float width, float height)
  : width_(width)
  , height_(height)
{

}

void Window::addGeometry(geometries::Geometry *element)
{
  geometries_.push_back(element);
  //cleanUp.push_back(std::unique_ptr<geometries::Geometry>(element));
}

std::vector<geometries::Geometry*> Window::getGeometries() const
{
  return geometries_;
}

