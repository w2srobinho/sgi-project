#include "window.h"

#include <memory>

Window::~Window()
{

}

Window::Window(const geometries::Point& min, const geometries::Point& max)
  : minPoint(min)
  , maxPoint(max)
{
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

const geometries::Point& Window::getMinPoint() const
{
  return minPoint;
}

const geometries::Point& Window::getMaxPoint() const
{
  return maxPoint;
}

void Window::verticalMove(float rate)
{
  minPoint.setY(minPoint.getY() + rate);
  maxPoint.setY(maxPoint.getY() + rate);
}

void Window::horizontalMove(float rate)
{
  minPoint.setX(minPoint.getX() + rate);
  maxPoint.setX(maxPoint.getX() + rate);
}

void Window::zoomIn()
{
  zoom(0.85f);
}

void Window::zoomOut()
{
  zoom(1.15f);
}

void Window::zoom(float factor)
{
  maxPoint *= factor;
}
