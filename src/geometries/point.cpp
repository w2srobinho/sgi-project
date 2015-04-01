#include "point.h"

namespace geometries {

  Point::~Point()
  {}
  
  Point::Point(float x, float y)
  : x_(x)
  , y_(y)
  , z_(0)
  {}

  Point::Point(const Point& other)
    : x_(other.getX())
    , y_(other.getY())
    , z_(other.getZ())
  {
  }

  const float& Point::getX() const
  {
    return x_;
  }

  const float& Point::getY() const
  {
    return y_;
  }

  const float& Point::getZ() const
  {
    return z_;
  }

  Point& Point::operator=(const Point& other)
  {
    if (this != &other) {
      x_ = other.getX();
      y_ = other.getY();
      z_ = other.getZ();
    }
    return *this;
  }
}
