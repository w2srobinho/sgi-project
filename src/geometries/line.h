#ifndef _INCLUDED_LINE_
#define _INCLUDED_LINE_

#include "geometry.h"
#include "point.h"

#include <initializer_list>

namespace geometries {
  class Line
      : public Geometry
  {
  public:
    ~Line();
    Line(const std::vector<Point>& points);
    Line(float x1, float y1, float x2, float y2, const std::string& name);
    Line(const Point& p1, const Point& p2, const std::string& name);
    Line(const std::vector<Point>& points, const std::string& name);

    const Point& getP1() const;
    const Point& getP2() const;

    Point center() const override;
    shape type() const override;
    std::vector<Point> getPoints() const override;
    const std::string& getName() const override;

    Geometry& operator *=(const Point& point) override;

  private:
    std::vector<Point> _points;
    std::string _name;
  };
}
#endif
