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
  : _x(x)
  , _y(y)
  , _z(1)
  {
  
  }

  Point::Point(const Point& other)
    : _x(other.getX())
    , _y(other.getY())
    , _z(other.getZ())
  {

  }

  Point::Point(std::vector<float> point)
    : Point(point.at(0), point.at(1))
  {
    
  }

  const float& Point::getX() const
  {
    return _x;
  }

  const float& Point::getY() const
  {
    return _y;
  }

  const float& Point::getZ() const
  {
    return _z;
  }

  std::vector<float> Point::get() const
  {
    return {_x, _y, _z};
  }

  void Point::setX(float newX)
  {
    _x = newX;
  }

  void Point::setY(float newY)
  {
    _y = newY;
  }

  void Point::setZ(float newZ)
  {
    _z = newZ;
  }

  bool Point::equals(const Point& other, float epsilon) const
  {
    return !((abs(_x - other.getX()) > epsilon) ||
            (abs(_y - other.getY()) > epsilon) ||
            (abs(_z - other.getZ()) > epsilon));
  }

  bool Point::operator<(const Point& other) const
  {

    return _x < other.getX() && _y < other.getY();
  }

  bool Point::operator>(const Point& other) const
  {

    return (other < *this);
  }

  Point& Point::operator*=(const Point& other)
  {
    _x *= other.getX();
    _y *= other.getY();
    _z *= other.getZ();
    return *this;
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
    _x *= number;
    _y *= number;
    return *this;
  }

  Point& Point::operator=(const Point& other)
  {
    if (this != &other) 
    {
      _x = other.getX();
      _y = other.getY();
      _z = other.getZ();
    }
    return *this;
  }
}
