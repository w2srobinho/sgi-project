#include "polygon.h"

namespace geometries {
  
  Polygon::~Polygon()
  {}

  Polygon::Polygon(const std::initializer_list<Point>& points)
    : points_(points)
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

  const std::vector<Point> &Polygon::getPoints() const
  {
    return points_;
  }

  ::geometries::type Polygon::type() const
  {
    return POLYGON;
  }
}
