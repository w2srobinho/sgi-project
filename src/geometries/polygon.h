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

    Point center() override;
    shape type() const override;
    std::vector<Point> getPoints() const override;
    const std::string& getName() const override;


  private:
    std::vector<Point> points_;
    std::string name_;
  };
}

#endif
