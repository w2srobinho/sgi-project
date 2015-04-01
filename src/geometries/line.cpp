#include "line.h"

namespace geometries {
  
  Line::~Line()
  {}

  Line::Line(float x1, float y1, float x2, float y2)
    : points_{Point(x1, y1), Point(x2, y2)}
  {}

  Line::Line(const Point& p1, const Point& p2)
    : points_{p1, p2}
  {}

  Line::Line(const std::initializer_list<Point> &points)
    : points_{points}
  {}

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

  const std::vector<Point>& Line::getPoints() const
  {
    return points_;
  }

  ::geometries::type Line::type() const
  {
    return LINE;
  }
}
