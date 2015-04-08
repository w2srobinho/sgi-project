#include "window.h"

#include <memory>

namespace
{
  const float WIDTH = 800;
  const float HEIGHT = 600;
}

Window::~Window()
{

}

Window::Window()
{

}

void Window::addGeometry(geometries::Geometry *element)
{
  geometries_.push_back(element);
  cleanUp.push_back(std::unique_ptr<geometries::Geometry>(element));
}

std::vector<geometries::Geometry*> Window::getGeometries() const
{
  return geometries_;
}


void Window::setWindowSize(float width, float height)
{
  width_ = width;
  height_ = height;
}


void Window::resetDefaultSize()
{
  width_ = WIDTH;
  height_ = HEIGHT;
}
