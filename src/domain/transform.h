#ifndef _INCLUDED_TRANSFORM_
#define _INCLUDED_TRANSFORM_

#include "geometry.h"

#include <cmath>
#include <vector>

namespace transform
{
  geometries::Point translation(const geometries::Point& point, float dx, float dy);
  void translation(geometries::Geometry* geometry, float dx, float dy);

  geometries::Point scaling(const geometries::Point& point, float sx, float sy);
  void scaling(geometries::Geometry* geometry, float sx, float sy);

  geometries::Point rotate(const geometries::Point& point, float angle);
  void rotate(geometries::Geometry* geometry, const geometries::Point& rotatePoint, float angle);
}

#endif
