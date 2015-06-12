#include "window.h"

#include <cassert>
#include <memory>

Window::~Window()
{

}

Window::Window(const geometries::Point& min, const geometries::Point& max)
  : minPoint(min)
  , maxPoint(max)
  , _angle(0)
{
}

void Window::addGeometry(geometries::Geometry *element)
{
  element->rotate(center(), -_angle);

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
  minPoint.translation(0, rate, 0);
  maxPoint.translation(0, rate, 0);
}

void Window::horizontalMove(float rate)
{
  minPoint.translation(rate, 0, 0);
  maxPoint.translation(rate, 0, 0);
}

geometries::Point Window::center() const
{
  float x = ((maxPoint.getX() - minPoint.getX()) / 2);
  float y = ((maxPoint.getY() - minPoint.getY()) / 2);
  float z = ((maxPoint.getZ() - minPoint.getZ()) / 2);

  geometries::Point _center = geometries::Point(x, y, z) + minPoint;
  return _center;
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
  minPoint *= factor;
  maxPoint *= factor;
}

void Window::translateGeometry(const std::string& geometryName, float dx, float dy, float dz)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->translation(dx, dy, dz);
}

void Window::scalingGeometry(const std::string& geometryName, float sx, float sy, float sz)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->scaling(sx, sy, sz);
}

void Window::rotateOrigin(const std::string& geometryName, float angle)
{
  assert(!displayFile.empty());
  auto geometry = displayFile[geometryName];
  geometry->rotate(angle);
}

void Window::rotateWindow(float angle)
{
  assert(!displayFile.empty());
  _angle += angle;
  
  if (_angle >= 360)
    _angle -= 360;

  for (auto geometry : displayFile)
    geometry.second->rotate(center(), -angle);
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
