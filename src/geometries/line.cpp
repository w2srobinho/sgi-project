#include "line.h"

namespace geometries {
  
  Line::~Line()
  {}

  Line::Line(double x1, double y1, double x2, double y2)
  : p1{Point(x1, y1)}
  , p2{Point(x2, y2)}
  {}

  Line::Line(const Point& p1, const Point& p2)
  : p1{p1}
  , p2{p2}
  {}

  const Point& Line::getP1() const
  {
    return p1;
  }

  const Point& Line::getP2() const
  {
    return p2;
  }
}
