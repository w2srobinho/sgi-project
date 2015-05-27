#include "window.h"

#include <cassert>
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
  _geometries.push_back(element);
  displayFile.insert({ element->getName(), element });
  cleanUp.push_back(std::unique_ptr<geometries::Geometry>(element));
}

std::vector<geometries::Geometry*> Window::getGeometries() const
{
  return _geometries;
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
  minPoint.translation(0, rate);
  maxPoint.translation(0, rate);
}

void Window::horizontalMove(float rate)
{
  minPoint.translation(rate, 0);
  maxPoint.translation(rate, 0);
}

geometries::Point Window::center() const
{
  float x = ((maxPoint.getX() - minPoint.getX()) / 2);
  float y = ((maxPoint.getY() - minPoint.getY()) / 2);

  return geometries::Point(x, y);
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

void Window::translateGeometry(const std::string& geometryName, float dx, float dy)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->translation(dx, dy);
}

void Window::scalingGeometry(const std::string& geometryName, float sx, float sy)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->scaling(sx, sy);
}

void Window::rotateOrigin(const std::string& geometryName, float angle)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->rotate(angle);
}

void Window::rotateWindow(const std::string& geometryName, float angle)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->rotate(center(), angle);
}

void Window::rotatePoint(
  const std::string& geometryName, 
  const geometries::Point& rotatePoint, 
  float angle)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->rotate(rotatePoint, angle);
}
