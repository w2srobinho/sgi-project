#include "polygon.h"

namespace geometries {
  
  Polygon::~Polygon()
  {
    for (auto point : _points)
    {
      delete point;
    }
  }

  Polygon::Polygon(const std::vector<Point*>& points)
    : Polygon(points, "Polygon")
  {

  }

  Polygon::Polygon(const std::vector<Point*>& points, const std::string& name)
    : _points(points)
    , _name(generateUniqueName(name))
  {

  }
  
  Point Polygon::center()
  {
    return geometryCenter(_points);
  }

  const std::vector<Point*>& Polygon::getPoints() const
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
}
