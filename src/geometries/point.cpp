#include "point.h"

namespace geometries {
  
  Point::~Point()
  {}
  
  Point::Point(double x, double y)
  : x{x}
  , y{y}
  {}

  Point::Point(const Point& other)
    : x{other.getX()}
    , y{other.getY()}
  {
  }

  const double& Point::getX() const
  {
    return x;
  }

  const double& Point::getY() const
  {
    return y;
  }

  Point& Point::operator=(const Point& other)
  {
    if (this != &other) {
      x = other.getX();
      y = other.getY();
    }
    return *this;
  }

}
