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
    Line(float x1, float y1, float x2, float y2);
    Line(const Point& p1, const Point& p2);
    Line(const std::initializer_list<Point>& points);

    const Point& getP1() const;
    const Point& getP2() const;

    Point center() override;
    const std::vector<Point>& getPoints() const override;
    ::geometries::type type() const override;

  private:
    std::vector<Point> points_;
  };
}
#endif
