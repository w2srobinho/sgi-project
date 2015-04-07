#include "graphicPoint.h"

namespace geometries {

  GraphicPoint::~GraphicPoint()
  {}


  GraphicPoint::GraphicPoint(float x, float y)
    : Point(x, y)
  {}

  Point GraphicPoint::center()
  {
    return Point(0, 0);
  }


  std::vector<Point> GraphicPoint::getPoints() const
  {
    return std::vector<Point> {Point(getX(), getY())};
  }


  shape GraphicPoint::type() const
  {
    return POINT;
  }

}
