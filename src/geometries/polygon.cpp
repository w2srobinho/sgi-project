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

  const Point& Polygon::getPointAt(std::size_t pos) const
  {
    return *_points.at(pos);
  }

  Point * const Polygon::operator[](std::size_t pos) const
  {
    return _points[pos];
  }

  bool Polygon::operator==(const Polygon& other) const
  {
    if (_points.size() != other.size())
      return false;

    for (std::size_t i = 0; i < _points.size(); ++i)
    {
      if (*_points.at(i) != other.getPointAt(i))
        return false;
    }
    return true;
  }

  bool Polygon::operator!=(const Polygon& other) const
  {
    return !(*this == other);
  }

  std::size_t Polygon::size() const
  {
    return _points.size();
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
