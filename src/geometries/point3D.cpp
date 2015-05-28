#include "point3D.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

namespace geometries {

  Point3D::~Point3D()
  {
  
  }

  Point3D::Point3D()
    : Point3D(0, 0, 0)
  {

  }
  
  Point3D::Point3D(float x, float y, float z)
    : _point({x, y, z, 1})
  {
  
  }

  Point3D::Point3D(const Point3D& other)
    : _point(other.get())
  {

  }
  
  const float& Point3D::getX() const
  {
    return _point.at(0);
  }

  const float& Point3D::getY() const
  {
    return _point.at(1);
  }

  const float& Point3D::getZ() const
  {
    return _point.at(2);
  }

  const std::vector<float>& Point3D::get() const
  {
    return _point;
  }

  void Point3D::translation(float dx, float dy, float dz)
  {
    std::vector<std::vector<float>> translateMatrix = { {  1,  0,  0, 0 },
                                                        {  0,  1,  0, 0 },
                                                        {  0,  0,  1, 0 },
                                                        { dx, dy, dz, 1 } };

    _point = dotProduct(_point, translateMatrix);
  }

  void Point3D::scaling(float sx, float sy, float sz)
  {
    std::vector<std::vector<float>> scalingMatrix = { { sx,  0,  0, 0 },
                                                      {  0, sy,  0, 0 },
                                                      {  0,  0, sz, 0 },
                                                      {  0,  0,  0, 1 } };

    _point = dotProduct(_point, scalingMatrix);
  }

  void Point3D::rotateX(float angle)
  {
    float _radiansAngle = radiansAngle(angle);
    float cos = std::cos(_radiansAngle);
    float sin = std::sin(_radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { 1,    0,   0, 0 },
                                                     { 0,  cos, sin, 0 },
                                                     { 0, -sin, cos, 0 },
                                                     { 0,    0,   0, 1 } };
    
    _point = dotProduct(_point, rotateMatrix);
  }

  void Point3D::rotateY(float angle)
  {
    float _radiansAngle = radiansAngle(angle);
    float cos = std::cos(_radiansAngle);
    float sin = std::sin(_radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { cos, 0, -sin, 0 },
                                                     {   0, 1,    0, 0 },
                                                     { sin, 0,  cos, 0 },
                                                     {   0, 0,    0, 1 } };

    _point = dotProduct(_point, rotateMatrix);
  }

  void Point3D::rotateZ(float angle)
  {
    float _radiansAngle = radiansAngle(angle);
    float cos = std::cos(_radiansAngle);
    float sin = std::sin(_radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { cos, sin, 0, 0 },
                                                     {-sin, cos, 0, 0 },
                                                     {   0,   0, 1, 0 },
                                                     {   0,   0, 0, 1 } };

    _point = dotProduct(_point, rotateMatrix);

  }

  bool Point3D::equals(const Point3D& other, float epsilon) const
  {
    assert(_point.size() == other.get().size());
    return !((std::abs(_point.at(0) - other.getX()) > epsilon) ||
             (std::abs(_point.at(1) - other.getY()) > epsilon) ||
             (std::abs(_point.at(2) - other.getZ()) > epsilon));
  }

  bool Point3D::operator<(const Point3D& other) const
  {
    assert(_point.size() == other.get().size());
    return _point.at(0) < other.getX() &&
           _point.at(1) < other.getY() &&
           _point.at(2) < other.getZ();
  }

  bool Point3D::operator>(const Point3D& other) const
  {
    return (other < *this);
  }

  Point3D& Point3D::operator+=(const Point3D& other)
  {
    assert(_point.size() == other.get().size());
    _point[0] += other.getX();
    _point[1] += other.getY();
    _point[2] += other.getZ();
    return *this;
  }

  bool Point3D::operator!=(const Point3D& other) const
  {
    return !(*this == other);
  }

  bool Point3D::operator==(const Point3D& other) const
  {
    const float EPSILON = 0.01f;
    return equals(other, EPSILON);
  }

  Point3D& Point3D::operator*=(float number)
  {
    _point[0] *= number;
    _point[1] *= number;
    _point[2] *= number;
    return *this;
  }

  Point3D& Point3D::operator=(const Point3D& other)
  {
    assert(_point.size() == other.get().size());
    if (this != &other) 
    {
      _point = other.get();
    }
    return *this;
  }

  float Point3D::radiansAngle(float angle)
  {
    return angle * static_cast<float>(M_PI) / 180.f;
  }

  std::vector<float> Point3D::dotProduct(
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
