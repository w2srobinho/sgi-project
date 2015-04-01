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
    Polygon(const std::initializer_list<Point>& points);

    std::vector<Point>::const_iterator begin() const;
    std::vector<Point>::const_iterator end() const;

    Point center() override;
    const std::vector<Point> &getPoints() const override;
    ::geometries::type type() const override;

  private:
    std::vector<Point> points_;
  };
}

#endif
