#include "line.h"

#include <cassert>

namespace geometries {
  
  Line::~Line()
  {}

  Line::Line(const std::vector<Point>& points)
    : Line(points, "Line")
  {
  }
  
  Line::Line(const Point& p1, const Point& p2, const std::string& name)
    : Line({p1, p2}, name)
  {
  }

  Line::Line(const std::vector<Point> &points, const std::string& name)
    : _points(points)
    , _name(generateUniqueName(name))
  {
  }

  const Point& Line::getP1() const
  {
    return _points.at(0);
  }

  const Point& Line::getP2() const
  {
    return _points.at(1);
  }

  Point Line::center() const
{
    return Point(0, 0);
  }

  std::vector<Point> Line::getPoints() const
  {
    assert(_points.size() == 2);
    return _points;
  }

  shape Line::type() const
  {
    return POLYGON;
  }

  const std::string& Line::getName() const
  {
    return _name;
  }

  Geometry& Line::operator*=(const Point& point)
  {
    for (auto &p : _points)
    {
      p *= point;
    }
    return *this;
  }

}
