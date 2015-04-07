#ifndef _INCLUDED_GEOMETRY_
#define _INCLUDED_GEOMETRY_

#include "point.h"

#include <vector>

namespace geometries {

  enum shape {POINT, LINE, POLYGON};

  class Geometry
  {
  public:
    virtual ~Geometry() {}

    virtual Point center() = 0;
    virtual std::vector<Point> getPoints() const = 0;
    virtual shape type() const = 0;
  };
}

#endif

