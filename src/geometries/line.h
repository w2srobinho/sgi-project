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
    Line(const std::vector<Point*>& points);
    Line(float x1, float y1, float x2, float y2, const std::string& name);
    Line(Point* p1, Point* p2, const std::string& name);
    Line(const std::vector<Point*>& points, const std::string& name);

    const Point& getP1() const;
    const Point& getP2() const;

    Point center() override;
    shape type() const override;
    const std::string& getName() const override;
    const std::vector<Point*>& getPoints() const override;
    
  private:
    std::vector<Point*> _points;
    std::string _name;
  };
}
#endif
