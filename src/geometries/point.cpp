#include "point.h"

namespace geometries {

  Point::~Point()
  {}
  
  Point::Point(const float& x, const float& y)
  : x{x}
  , y{y}
  {}

  Point::Point(const Point& other)
    : x{other.getX()}
    , y{other.getY()}
  {
  }

  const float& Point::getX() const
  {
    return x;
  }

  const float& Point::getY() const
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
