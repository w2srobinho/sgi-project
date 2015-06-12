#ifndef _INCLUDED_BEZIER_
#define _INCLUDED_BEZIER_

#include "point.h"
#include "polygon.h"

#include <vector>

namespace geometries {
  class Bezier
      : public Polygon
  {
  public:
    ~Bezier();
    Bezier(const std::vector<Point*>& points);
    Bezier(const std::vector<Point*>& points, const std::string& name);
    
    shape type() const override;

    std::vector<Point> getBezierPoints(float maxT);

  private:
    geometries::Point quadraticBezier(
      const geometries::Point& p0,
      const geometries::Point& p1,
      const geometries::Point& p2,
      float t);

    geometries::Point cubicBezier(
      const geometries::Point& p0,
      const geometries::Point& p1,
      const geometries::Point& p2,
      const geometries::Point& p3,
      float t);    
  };
}

#endif
