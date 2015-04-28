#include "polygon.h"

namespace geometries {
  
  Polygon::~Polygon()
  {}

  Polygon::Polygon(const std::vector<Point>& points)
    : Polygon(points, "Polygon")
  {

  }

  Polygon::Polygon(const std::vector<Point>& points, const std::string& name)
    : _points(points)
    , _name(generateUniqueName(name))
  {

  }

  std::vector<Point>::const_iterator Polygon::begin() const
  {
    return _points.begin();
  }

  std::vector<Point>::const_iterator Polygon::end() const
  {
    return _points.end();
  }

  Point Polygon::center() const
{
    return Point(0, 0);
  }

  std::vector<Point> Polygon::getPoints() const
  {
    return _points;
  }

  shape Polygon::type() const
  {
    return POLYGON;
  }

  const std::string& Polygon::getName() const
  {
    return _name;
  }

  Geometry& Polygon::operator*=(const Point& point)
  {
    for (auto &p : _points)
    {
      p *= point;
    }
    return *this;
  }

}
