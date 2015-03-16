#ifndef _INCLUDED_POINT_
#define _INCLUDED_POINT_

#include "geometry.h"

namespace geometries {
  class Point
      : public Geometry
  {
  public:
    ~Point();
    Point(double x, double y);
    Point(const Point& other);

    const double& getX() const;
    const double& getY() const;

    Point& operator=(const Point& other);

  private:
    double x;
    double y;
  };
}
#endif
