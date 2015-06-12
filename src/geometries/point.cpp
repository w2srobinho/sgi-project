#include "point.h"

#include <cassert>

#ifdef _MSC_VER
# define _USE_MATH_DEFINES
# include <math.h>
#else
# include <cmath>
#endif

namespace geometries {

  Point::~Point()
  {
  
  }

  Point::Point()
    : Point(0, 0, 0)
  {

  }

  Point::Point(float x, float y)
    : Point(x, y, 0)
  {

  }

  Point::Point(float x, float y, float z)
    : _point({ x, y, z, 1 })
  {

  }

  Point::Point(const Point& other)
    : _point(other.get())
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

  const float& Point::getZ() const
  {
    return _point.at(2);
  }

  const std::vector<float>& Point::get() const
  {
    return _point;
  }

  void Point::translation(float dx, float dy, float dz)
  {
    std::vector<std::vector<float>> translateMatrix = { {  1,  0,  0, 0 },
                                                        {  0,  1,  0, 0 },
                                                        {  0,  0,  1, 0 },
                                                        { dx, dy, dz, 1 } };

    _point = dotProduct(_point, translateMatrix);
  }

  void Point::scaling(float sx, float sy, float sz)
  {
    std::vector<std::vector<float>> scalingMatrix = { { sx,  0,  0, 0 },
                                                      {  0, sy,  0, 0 },
                                                      {  0,  0, sz, 0 },
                                                      {  0,  0,  0, 1 } };

    _point = dotProduct(_point, scalingMatrix);
  }

  void Point::rotateX(float angle)
  {
    float _radiansAngle = radiansAngle(angle);
    float _cos = cos(_radiansAngle);
    float _sin = sin(_radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { 1,     0,    0, 0 },
                                                     { 0,  _cos, _sin, 0 },
                                                     { 0, -_sin, _cos, 0 },
                                                     { 0,     0,    0, 1 } };
    
    _point = dotProduct(_point, rotateMatrix);
  }

  void Point::rotateY(float angle)
  {
    float _radiansAngle = radiansAngle(angle);
    float _cos = cos(_radiansAngle);
    float _sin = sin(_radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { _cos, 0, -_sin, 0 },
                                                     {    0, 1,     0, 0 },
                                                     { _sin, 0,  _cos, 0 },
                                                     {   0,  0,     0, 1 } };

    _point = dotProduct(_point, rotateMatrix);
  }

  void Point::rotateZ(float angle)
  {
    float _radiansAngle = radiansAngle(angle);
    float _cos = cos(_radiansAngle);
    float _sin = sin(_radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { _cos, _sin, 0, 0 },
                                                     {-_sin, _cos, 0, 0 },
                                                     {    0,    0, 1, 0 },
                                                     {    0,    0, 0, 1 } };

    _point = dotProduct(_point, rotateMatrix);

  }

  bool Point::equals(const Point& other, float epsilon) const
  {
    assert(_point.size() == other.get().size());
    return !((std::abs(_point.at(0) - other.getX()) > epsilon) ||
             (std::abs(_point.at(1) - other.getY()) > epsilon) ||
             (std::abs(_point.at(2) - other.getZ()) > epsilon));
  }

  bool Point::operator<(const Point& other) const
  {
    assert(_point.size() == other.get().size());
    return _point.at(0) < other.getX() &&
           _point.at(1) < other.getY() &&
           _point.at(2) < other.getZ();
  }

  bool Point::operator>(const Point& other) const
  {
    return (other < *this);
  }

  Point& Point::operator+=(const Point& other)
  {
    assert(_point.size() == other.get().size());
    _point[0] += other.getX();
    _point[1] += other.getY();
    _point[2] += other.getZ();
    return *this;
  }

  Point Point::operator+(const Point& other)
  {
    return *this += other;
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
    _point[2] *= number;
    return *this;
  }

  Point& Point::operator=(const Point& other)
  {
    assert(_point.size() == other.get().size());
    if (this != &other) 
    {
      _point = other.get();
    }
    return *this;
  }

  float Point::radiansAngle(float angle)
  {
    return angle * static_cast<float>(M_PI) / 180.f;
  }

  std::vector<float> Point::dotProduct(
    const std::vector<float>& _vector,
    const std::vector<std::vector<float>>& _matrix)
  {
    assert(_vector.size() == _matrix.size());  // mXn * nXk, columns == lines  

    std::vector<float> newVec = { 0, 0, 0, 0 };

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
