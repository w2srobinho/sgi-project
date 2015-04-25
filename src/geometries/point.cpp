#include "point.h"

namespace geometries {

  Point::~Point()
  {
  
  }

  Point::Point()
    : Point(0, 0)
  {

  }
  
  Point::Point(float x, float y)
  : x_(x)
  , y_(y)
  , z_(1)
  {
  
  }

  Point::Point(const Point& other)
    : x_(other.getX())
    , y_(other.getY())
    , z_(other.getZ())
  {

  }

  Point::Point(std::vector<float> point)
    : Point(point.at(0), point.at(1))
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

  std::vector<float> Point::get() const
  {
    return {x_, y_, z_};
  }

  void Point::setX(float newX)
  {
    x_ = newX;
  }

  void Point::setY(float newY)
  {
    y_ = newY;
  }

  void Point::setZ(float newZ)
  {
    z_ = newZ;
  }

  bool Point::equals(const Point& other, float epsilon) const
  {
    return !((abs(x_ - other.getX()) > epsilon) ||
            (abs(y_ - other.getY()) > epsilon) ||
            (abs(z_ - other.getZ()) > epsilon));
  }

  bool Point::operator<(const Point& other) const
  {

    return x_ < other.getX() && y_ < other.getY();
  }

  bool Point::operator>(const Point& other) const
  {

    return (other < *this);
  }

  bool Point::operator!=(const Point& other) const
  {

    return !(*this == other);
  }

  bool Point::operator==(const Point& other) const
  {
    const float EPSILON = 0.01f;
    return equals(other, EPSILON);
  }

  Point& Point::operator*=(float number)
  {
    x_ *= number;
    y_ *= number;
    return *this;
  }

  Point& Point::operator=(const Point& other)
  {
    if (this != &other) 
    {
      x_ = other.getX();
      y_ = other.getY();
      z_ = other.getZ();
    }
    return *this;
  }
}
