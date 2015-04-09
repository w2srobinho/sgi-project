#include "graphicPoint.h"

namespace geometries {

  GraphicPoint::~GraphicPoint()
  {}

  GraphicPoint::GraphicPoint(float x, float y)
    : GraphicPoint(x, y, "Point")
  {}

  GraphicPoint::GraphicPoint(float x, float y, const std::string& name)
    : Point(x, y)
    , name_(generateUniqueName(name))
  {}

  Point GraphicPoint::center()
  {
    return Point(0, 0);
  }

  std::vector<Point> GraphicPoint::getPoints() const
  {
    return std::vector<Point> {Point(getX(), getY())};
  }

  const std::string& GraphicPoint::getName() const
  {
    return name_;
  }

  shape GraphicPoint::type() const
  {
    return POINT;
  }

}
