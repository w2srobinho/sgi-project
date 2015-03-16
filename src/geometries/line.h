#ifndef _INCLUDED_LINE_
#define _INCLUDED_LINE_

#include "geometry.h"
#include "point.h"

namespace geometries {
  class Line
      : public Geometry
  {
  public:
    ~Line();
    Line(double x1, double y1, double x2, double y2);
    Line(const Point& p1, const Point& p2);

    const Point& getP1() const;
    const Point& getP2() const;

  private:
    Point p1;
    Point p2;
  };
}
#endif
