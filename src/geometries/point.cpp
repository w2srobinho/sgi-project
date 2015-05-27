#include "point.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace geometries {

  Point::~Point()
  {
  
  }

  Point::Point()
    : Point(0, 0)
  {

  }
  
  Point::Point(float x, float y)
    : _point({x, y, 1})
  {
  
  }

  Point::Point(const Point& other)
    : _point(other.get())
  {

  }

  Point::Point(std::vector<float> point)
    : Point(point.at(0), point.at(1))
  {
    
  }

  const float& Point::getX() const
  {
    return _point.at(0);
  }

  const float& Point::getY() const
  {
    return _point.at(1);
  }

  const std::vector<float>& Point::get() const
  {
    return _point;
  }

  void Point::translation(float dx, float dy)
  {
    std::vector<std::vector<float>> translateMatrix = { {  1,  0, 0 },
                                                        {  0,  1, 0 },
                                                        { dx, dy, 1 } };

    std::vector<float> pNew = { 0, 0, 0 };
    
    for (std::size_t i = 0; i < translateMatrix.size(); ++i)
    {
      for (std::size_t j = 0; j < translateMatrix[i].size(); ++j)
      {
        pNew[j] += _point.at(i) * translateMatrix[i][j];
      }
    }
    _point = pNew;
  }

  void Point::scaling(float sx, float sy)
  {
    std::vector<std::vector<float>> scalingMatrix = { { sx,  0, 0 },
                                                      {  0, sy, 0 },
                                                      {  0,  0, 1 } };

    std::vector<float> pNew = { 0, 0, 0 };

    for (std::size_t i = 0; i < scalingMatrix.size(); ++i)
    {
      for (std::size_t j = 0; j < scalingMatrix[i].size(); ++j)
      {
        pNew[j] += _point.at(i) * scalingMatrix[i][j];
      }
    }

    _point = pNew;
  }

  void Point::rotate(float angle)
  {
    float radiansAngle = angle * M_PI / 180.f;
    float cos = std::cos(radiansAngle);
    float sin = std::sin(radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { cos, -sin, 0 },
                                                     { sin,  cos, 0 },
                                                     {   0,    0, 1 } };


    std::vector<float> pNew = { 0, 0, 0 };

    for (std::size_t i = 0; i < rotateMatrix.size(); ++i)
    {
      for (std::size_t j = 0; j < rotateMatrix[i].size(); ++j)
      {
        pNew[j] += _point.at(i) * rotateMatrix[i][j];
      }
    }

    _point = pNew;
  }

  bool Point::equals(const Point& other, float epsilon) const
  {
    return !((std::abs(_point.at(0) - other.getX()) > epsilon) ||
             (std::abs(_point.at(1) - other.getY()) > epsilon));
  }

  bool Point::operator<(const Point& other) const
  {

    return _point.at(0) < other.getX() &&
           _point.at(1) < other.getY();
  }

  bool Point::operator>(const Point& other) const
  {

    return (other < *this);
  }

  Point& Point::operator+=(const Point& other)
  {
    _point[0] += other.getX();
    _point[1] += other.getY();
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
    _point[0] *= number;
    _point[1] *= number;
    return *this;
  }

  Point& Point::operator=(const Point& other)
  {
    if (this != &other) 
    {
      _point = other.get();
    }
    return *this;
  }
}
