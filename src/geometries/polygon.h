#ifndef _INCLUDED_POLYGON_
#define _INCLUDED_POLYGON_

#include "geometry.h"
#include "point.h"

#include <vector>

namespace geometries {
  class Polygon
      : public Geometry
  {
  public:
    ~Polygon();
    Polygon(const std::vector<Point>& points);
    Polygon(const std::vector<Point>& points, const std::string& name);

    std::vector<Point>::const_iterator begin() const;
    std::vector<Point>::const_iterator end() const;

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
