#include "point2D.h"

#include <cassert>

#ifdef _MSC_VER
# define _USE_MATH_DEFINES
# include <math.h>
#else
# include <cmath>
#endif

namespace geometries {

  Point2d::~Point2d()
  {
  
  }

  Point2d::Point2d()
    : Point2d(0, 0)
  {

  }
  
  Point2d::Point2d(float x, float y)
    : _point({x, y, 1})
  {
  
  }

  Point2d::Point2d(const Point2d& other)
    : _point(other.get())
  {

  }

  const float& Point2d::getX() const
  {
    return _point.at(0);
  }

  const float& Point2d::getY() const
  {
    return _point.at(1);
  }

  const std::vector<float>& Point2d::get() const
  {
    return _point;
  }

  void Point2d::translation(float dx, float dy)
  {
    std::vector<std::vector<float>> translateMatrix = { {  1,  0, 0 },
                                                        {  0,  1, 0 },
                                                        { dx, dy, 1 } };

    _point = dotProduct(_point, translateMatrix);
  }

  void Point2d::scaling(float sx, float sy)
  {
    std::vector<std::vector<float>> scalingMatrix = { { sx,  0, 0 },
                                                      {  0, sy, 0 },
                                                      {  0,  0, 1 } };

    _point = dotProduct(_point, scalingMatrix);
  }

  void Point2d::rotate(float angle)
  {
    float radiansAngle = angle * static_cast<float>(M_PI) / 180.f;
    float _cos = cos(radiansAngle);
    float _sin = sin(radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { _cos, -_sin, 0 },
                                                     { _sin,  _cos, 0 },
                                                     {    0,     0, 1 } };

    _point = dotProduct(_point, rotateMatrix);
  }

  bool Point2d::equals(const Point2d& other, float epsilon) const
  {
    assert(_point.size() == other.get().size());
    return !((std::abs(_point.at(0) - other.getX()) > epsilon) ||
             (std::abs(_point.at(1) - other.getY()) > epsilon));
  }

  bool Point2d::operator<(const Point2d& other) const
  {
    assert(_point.size() == other.get().size());
    return _point.at(0) < other.getX() &&
           _point.at(1) < other.getY();
  }

  bool Point2d::operator>(const Point2d& other) const
  {
    return (other < *this);
  }

  Point2d& Point2d::operator+=(const Point2d& other)
  {
    assert(_point.size() == other.get().size());
    _point[0] += other.getX();
    _point[1] += other.getY();
    return *this;
  }

  bool Point2d::operator!=(const Point2d& other) const
  {
    return !(*this == other);
  }

  bool Point2d::operator==(const Point2d& other) const
  {
    const float EPSILON = 0.01f;
    return equals(other, EPSILON);
  }

  Point2d& Point2d::operator*=(float number)
  {
    _point[0] *= number;
    _point[1] *= number;
    return *this;
  }

  Point2d& Point2d::operator=(const Point2d& other)
  {
    assert(_point.size() == other.get().size());
    if (this != &other) 
    {
      _point = other.get();
    }
    return *this;
  }

  std::vector<float> Point2d::dotProduct(
    const std::vector<float>& _vector,
    const std::vector<std::vector<float>>& _matrix)
  {
    assert(_vector.size() == _matrix.size());  // mXn * nXk, columns == lines  

    std::vector<float> newVec = { 0, 0, 0 };

    for (std::size_t i = 0; i < _matrix.size(); ++i)
    {
      for (std::size_t j = 0; j < _matrix[i].size(); ++j)
      {
        newVec[j] += _vector[i] * _matrix[i][j];
      }
    }

    return newVec;
  }
}
