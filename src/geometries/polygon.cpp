#include "polygon.h"

namespace geometries {
  
  Polygon::~Polygon()
  {}

  Polygon::Polygon(std::vector<Point> points)
  {
    Point first(*std::begin(points));
    Point previous(first);
    for(auto it = ++std::begin(points); it != std::end(points); ++it)
    {
      lines.push_back(Line(previous, *it));
      previous = *it;
    }

    lines.push_back(Line(*std::end(points), first));
  }

  std::vector<Line>::const_iterator Polygon::begin() const
  {
    return lines.begin();
  }

  std::vector<Line>::const_iterator Polygon::end() const
  {
    return lines.end();
  }

  Point center()
  {
    return Point(0, 0);
  }
}
