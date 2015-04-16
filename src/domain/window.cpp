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

std::pair<geometries::Point, geometries::Point> Window::getWindowPoints() const
{
  return std::pair<geometries::Point, geometries::Point> {minPoint, maxPoint};
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

geometries::Point Window::toViewPort(
  const geometries::Point& pointOnWindow,
  const geometries::Point& vpMinPoint, 
  const geometries::Point& vpMaxPoint)
{
  /**
  * Xvp = ((Xw - Xwmin) / (Xwmax - Xwmin)) * (Xvpmax - Xvpmin)
  */
  auto windowWidth = maxPoint.getX() - minPoint.getX();
  auto viewPortWidth = vpMaxPoint.getX() - vpMinPoint.getX();
  auto xvp = ((pointOnWindow.getX() - minPoint.getX()) / (windowWidth)) * viewPortWidth;
    
  /**
  * Yvp = (1 - ((Yw - Ywmin) / (Ywmax - Ywmin))) * (Yvpmax - Yvpmin)
  */
  auto windowHeight = maxPoint.getY() - minPoint.getY();
  auto viewPortHeight = vpMaxPoint.getY() - vpMinPoint.getY();
  auto yvp = (1 - ((pointOnWindow.getY() - minPoint.getY()) / (windowHeight))) * viewPortHeight;
  
  return geometries::Point(xvp, yvp);
}
