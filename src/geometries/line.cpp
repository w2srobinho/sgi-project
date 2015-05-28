#include "line.h"

#include <cassert>

namespace geometries {
  
  Line::~Line()
  {
    for (auto point : _points)
    {
      delete point;
    }
  }

  Line::Line(const std::vector<Point2D*>& points)
    : Line(points, "Line")
  {
  }
  
  Line::Line(Point2D* p1, Point2D* p2, const std::string& name)
    : Line({p1, p2}, name)
  {
  }

  Line::Line(const std::vector<Point2D*> &points, const std::string& name)
    : _points(points)
    , _name(generateUniqueName(name))
  {
  }

  const Point2D& Line::getP1() const
  {
    return *_points.at(0);
  }

  const Point2D& Line::getP2() const
  {
    return *_points.at(1);
  }

  const std::vector<Point2D*>& Line::getPoints() const
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
}
