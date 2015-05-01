#include "window.h"

#include "transform.h"

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
  minPoint.setY(minPoint.getY() + rate);
  maxPoint.setY(maxPoint.getY() + rate);
}

void Window::horizontalMove(float rate)
{
  minPoint.setX(minPoint.getX() + rate);
  maxPoint.setX(maxPoint.getX() + rate);
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
  transform::translation(geometry, dx, dy);
}

void Window::rotateOrigin(const std::string& geometryName, float angle)
{
  auto transformPoint = transform::rotate(minPoint, angle);
  auto geometry = displayFile[geometryName];

  //*geometry *= transformPoint;
}

void Window::rotateWindow(const std::string& geometryName, float angle)
{
  auto transformPoint = transform::rotate(center(), angle);
  auto geometry = displayFile[geometryName];

  //*geometry *= transformPoint;
}

void Window::rotatePoint(
  const std::string& geometryName, 
  const geometries::Point& rotatePoint, 
  float angle)
{
  auto transformPoint = transform::rotate(rotatePoint, angle);
  auto geometry = displayFile[geometryName];

  //*geometry *= transformPoint;
}
