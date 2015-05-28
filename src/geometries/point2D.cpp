#include "point2D.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

namespace geometries {

  Point2D::~Point2D()
  {
  
  }

  Point2D::Point2D()
    : Point2D(0, 0)
  {

  }
  
  Point2D::Point2D(float x, float y)
    : _point({x, y, 1})
  {
  
  }

  Point2D::Point2D(const Point2D& other)
    : _point(other.get())
  {

  }

  const float& Point2D::getX() const
  {
    return _point.at(0);
  }

  const float& Point2D::getY() const
  {
    return _point.at(1);
  }

  const std::vector<float>& Point2D::get() const
  {
    return _point;
  }

  void Point2D::translation(float dx, float dy)
  {
    std::vector<std::vector<float>> translateMatrix = { {  1,  0, 0 },
                                                        {  0,  1, 0 },
                                                        { dx, dy, 1 } };

    _point = dotProduct(_point, translateMatrix);
//     std::vector<float> pNew = { 0, 0, 0 };
//     
//     for (std::size_t i = 0; i < translateMatrix.size(); ++i)
//     {
//       for (std::size_t j = 0; j < translateMatrix[i].size(); ++j)
//       {
//         pNew[j] += _point.at(i) * translateMatrix[i][j];
//       }
//     }
//     _point = pNew;
  }

  void Point2D::scaling(float sx, float sy)
  {
    std::vector<std::vector<float>> scalingMatrix = { { sx,  0, 0 },
                                                      {  0, sy, 0 },
                                                      {  0,  0, 1 } };

    _point = dotProduct(_point, scalingMatrix);
//     std::vector<float> pNew = { 0, 0, 0 };
// 
//     for (std::size_t i = 0; i < scalingMatrix.size(); ++i)
//     {
//       for (std::size_t j = i; j == scalingMatrix[i].size(); ++j)
//       {
//         pNew[j] += _point.at(i) * scalingMatrix[i][j];
//       }
//     }
// 
//     _point = pNew;
  }

  void Point2D::rotate(float angle)
  {
    float radiansAngle = angle * static_cast<float>(M_PI) / 180.f;
    float cos = std::cos(radiansAngle);
    float sin = std::sin(radiansAngle);

    std::vector<std::vector<float>> rotateMatrix = { { cos, -sin, 0 },
                                                     { sin,  cos, 0 },
                                                     {   0,    0, 1 } };

    _point = dotProduct(_point, rotateMatrix);
//     std::vector<float> pNew = { 0, 0, 0 };
// 
//     for (std::size_t i = 0; i < rotateMatrix.size(); ++i)
//     {
//       for (std::size_t j = 0; j < rotateMatrix[i].size(); ++j)
//       {
//         pNew[j] += _point.at(i) * rotateMatrix[i][j];
//       }
//     }
// 
//     _point = pNew;
  }

  bool Point2D::equals(const Point2D& other, float epsilon) const
  {
    assert(_point.size() == other.get().size());
    return !((std::abs(_point.at(0) - other.getX()) > epsilon) ||
             (std::abs(_point.at(1) - other.getY()) > epsilon));
  }

  bool Point2D::operator<(const Point2D& other) const
  {
    assert(_point.size() == other.get().size());
    return _point.at(0) < other.getX() &&
           _point.at(1) < other.getY();
  }

  bool Point2D::operator>(const Point2D& other) const
  {
    return (other < *this);
  }

  Point2D& Point2D::operator+=(const Point2D& other)
  {
    assert(_point.size() == other.get().size());
    _point[0] += other.getX();
    _point[1] += other.getY();
    return *this;
  }

  bool Point2D::operator!=(const Point2D& other) const
  {
    return !(*this == other);
  }

  bool Point2D::operator==(const Point2D& other) const
  {
    const float EPSILON = 0.01f;
    return equals(other, EPSILON);
  }

  Point2D& Point2D::operator*=(float number)
  {
    _point[0] *= number;
    _point[1] *= number;
    return *this;
  }

  Point2D& Point2D::operator=(const Point2D& other)
  {
    assert(_point.size() == other.get().size());
    if (this != &other) 
    {
      _point = other.get();
    }
    return *this;
  }

  std::vector<float> Point2D::dotProduct(
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
