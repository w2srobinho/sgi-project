#include "window.h"

#include <memory>

Window::~Window()
{

}

Window::Window(float width, float height)
  : width_(width)
  , height_(height)
{
  defaultWidth = width_;
}

void Window::addGeometry(geometries::Geometry *element)
{
  geometries_.push_back(element);
  displayFile.insert({ element->getName(), element });
  cleanUp.push_back(std::unique_ptr<geometries::Geometry>(element));
}

std::vector<geometries::Geometry*> Window::getGeometries() const
{
  return geometries_;
}

std::pair<float, float> Window::getWindowSize() const
{
  return std::pair<float, float> {width_, height_};
}

std::pair<geometries::Point, geometries::Point> Window::getWindowPoints() const
{
  geometries::Point p1(0, 0);
  geometries::Point p2(width_, height_);
  return std::pair<geometries::Point, geometries::Point> {p1, p2};
}

void Window::zoomIn()
{
  zoom(1.15f);
}

void Window::zoomOut()
{
  zoom(0.85f);
}

float Window::getActualAmount() const
{
  return width_ / defaultWidth * 100;
}

void Window::zoom(float factor)
{
  width_ *= factor;
  height_ *= factor;
}
