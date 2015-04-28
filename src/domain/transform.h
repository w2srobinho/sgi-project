#ifndef _INCLUDED_TRANSFORM_
#define _INCLUDED_TRANSFORM_

#include "geometry.h"

#include <cmath>
#include <vector>

namespace transform
{
  geometries::Point translation(const geometries::Point& point, float dx, float dy);

  geometries::Point scaling(const geometries::Point& point, float sx, float sy);

  geometries::Point rotate(const geometries::Point& point, float angle);
}

#endif
