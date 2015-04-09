#include "line.h"

#include <cassert>

namespace geometries {
  
  Line::~Line()
  {}

  Line::Line(const std::initializer_list<Point> &points)
    : Line(points, "Line")
  {
  }
  
  Line::Line(const Point& p1, const Point& p2, const std::string& name)
    : Line({p1, p2}, name)
  {
  }

  Line::Line(const std::vector<Point> &points, const std::string& name)
    : points_(points)
    , name_(generateUniqueName(name))
  {
  }

  const Point& Line::getP1() const
  {
    return points_.at(0);
  }

  const Point& Line::getP2() const
  {
    return points_.at(1);
  }

  Point Line::center()
  {
    return Point(0, 0);
  }

  std::vector<Point> Line::getPoints() const
  {
    assert(points_.size() == 2);
    return points_;
  }

  shape Line::type() const
  {
    return LINE;
  }

  const std::string& Line::getName() const
  {
    return name_;
  }

}
