#ifndef _INCLUDED_LINE_
#define _INCLUDED_LINE_

#include "geometry.h"
#include "point2D.h"

#include <initializer_list>

namespace geometries {
  class Line
      : public Geometry
  {
  public:
    ~Line();
    Line(const std::vector<Point2D*>& points);
    Line(float x1, float y1, float x2, float y2, const std::string& name);
    Line(Point2D* p1, Point2D* p2, const std::string& name);
    Line(const std::vector<Point2D*>& points, const std::string& name);

    const Point2D& getP1() const;
    const Point2D& getP2() const;

    shape type() const override;
    const std::string& getName() const override;
    const std::vector<Point2D*>& getPoints() const override;

  private:
    std::vector<Point2D*> _points;
    std::string _name;
  };
}
#endif
