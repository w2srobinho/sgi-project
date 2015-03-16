#ifndef _INCLUDED_POLYGON_
#define _INCLUDED_POLYGON_

#include "geometry.h"
#include "line.h"
#include "point.h"

#include <vector>

namespace geometries {
  class Polygon
      : public Geometry
  {
  public:
    ~Polygon();
    Polygon(std::vector<Point> points);

    std::vector<Line>::const_iterator begin() const;
    std::vector<Line>::const_iterator end() const;

  private:
    std::vector<Line> lines;
  };
}
#endif
