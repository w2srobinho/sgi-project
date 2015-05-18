#include "bezier.h"

#include <cassert>
#include <cmath>

namespace geometries {
  
  /* Bezier Matrix Transformation */
  std::vector<std::vector<float>> MB = { {-1,  3, -3, 1},
                                         { 3, -6,  3, 0},
                                         {-3,  3,  0, 0},
                                         { 1,  0,  0, 0} };


  Bezier::~Bezier()
  {
  }

  Bezier::Bezier(const std::vector<Point*>& points)
    : Bezier(points, "Curve")
  {

  }

  Bezier::Bezier(const std::vector<Point*>& points, const std::string& name)
    : Polygon(points, name)
  {
    assert(points.size() >= 3);
  }
  
  std::vector<Point> Bezier::getBezierPoints(float maxT)
  {
    maxT += 0.01f;
    auto _points = getPoints();
    assert(_points.size() >= 3u && _points.size() <= 4u);
    std::vector<Point> bezierPoints;
    
    float step = 0.05f;

    if (_points.size() == 3u)
    {
      for (float t = 0; t <= maxT; t += step)
        bezierPoints.push_back(quadraticBezier(*_points[0], *_points[1], *_points[2], t));
    }
    else if (_points.size() == 4u)
    {
      for (float t = 0; t <= maxT; t += step)
        bezierPoints.push_back(cubicBezier(*_points[0], *_points[1], *_points[2], *_points[3], t));
    }

    return bezierPoints;
  }

  geometries::Point Bezier::quadraticBezier(
    const geometries::Point& p0,
    const geometries::Point& p1, 
    const geometries::Point& p2, 
    float t)
  {
    float x = powf(1 - t, 2) * p0.getX() +
              (1 - t) * 2 * t * p1.getX() +
              t * t * p2.getX();
    float y = powf(1 - t, 2) * p0.getY() +
              (1 - t) * 2 * t * p1.getY() +
              t * t * p2.getY();

    return geometries::Point(x, y);
  }

  geometries::Point Bezier::cubicBezier(
    const geometries::Point& p0,
    const geometries::Point& p1,
    const geometries::Point& p2,
    const geometries::Point& p3,
    float t)
  {
    float x = powf(1 - t, 3) * p0.getX() +
              powf(1 - t, 2) * 3 * t * p1.getX() +
              (1 - t) * 3 * t * t * p2.getX() +
              t * t * t * p3.getX();
    float y = powf(1 - t, 3) * p0.getY() +
              powf(1 - t, 2) * 3 * t * p1.getY() +
              (1 - t) * 3 * t * t * p2.getY() +
              t * t * t * p3.getY();

    return geometries::Point(x, y);
  }

  shape Bezier::type() const
  {
    return BEZIER;
  }

}
