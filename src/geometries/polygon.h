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

    std::size_t size() const;
    
    shape type() const override;
    const std::string& getName() const override;
    const std::vector<Point*>& getPoints() const override;
        
    const Point& getPointAt(std::size_t pos) const;
    Point * const operator[](std::size_t pos) const;
    bool operator==(const Polygon& other) const;
    bool operator!=(const Polygon& other) const;

  private:
    std::vector<Point*> _points;
    std::string _name;
  };
}

#endif
