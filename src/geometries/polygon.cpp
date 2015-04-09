#include "polygon.h"

namespace geometries {
  
  Polygon::~Polygon()
  {}

  Polygon::Polygon(const std::vector<Point>& points)
    : Polygon(points, "Polygon")
  {

  }

  Polygon::Polygon(const std::vector<Point>& points, const std::string& name)
    : points_(points)
    , name_(generateUniqueName(name))
  {

  }

  std::vector<Point>::const_iterator Polygon::begin() const
  {
    return points_.begin();
  }

  std::vector<Point>::const_iterator Polygon::end() const
  {
    return points_.end();
  }

  Point Polygon::center()
  {
    return Point(0, 0);
  }

  std::vector<Point> Polygon::getPoints() const
{
    return points_;
  }

  shape Polygon::type() const
  {
    return POLYGON;
  }

  const std::string& Polygon::getName() const
  {
    return name_;
  }

}
