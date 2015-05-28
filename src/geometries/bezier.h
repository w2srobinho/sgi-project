#ifndef _INCLUDED_BEZIER_
#define _INCLUDED_BEZIER_

#include "point2D.h"
#include "polygon.h"

#include <vector>

namespace geometries {
  class Bezier
      : public Polygon
  {
  public:
    ~Bezier();
    Bezier(const std::vector<Point2D*>& points);
    Bezier(const std::vector<Point2D*>& points, const std::string& name);
    
    shape type() const override;

    std::vector<Point2D> getBezierPoints(float maxT);

  private:
    geometries::Point2D quadraticBezier(
      const geometries::Point2D& p0,
      const geometries::Point2D& p1,
      const geometries::Point2D& p2,
      float t);

    geometries::Point2D cubicBezier(
      const geometries::Point2D& p0,
      const geometries::Point2D& p1,
      const geometries::Point2D& p2,
      const geometries::Point2D& p3,
      float t);    
  };
}

#endif
