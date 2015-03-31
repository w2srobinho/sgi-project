#ifndef _INCLUDED_GEOMETRY_
#define _INCLUDED_GEOMETRY_

#include "point.h"

namespace geometries {
  class Geometry
  {
  public:
    virtual ~Geometry() {};

    virtual Point center() = 0;
  };
}

#endif

