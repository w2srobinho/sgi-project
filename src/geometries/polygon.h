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
    Polygon(const std::vector<Point*>& points);
    Polygon(const std::vector<Point*>& points, const std::string& name);
    
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
