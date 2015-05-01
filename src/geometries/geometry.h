#ifndef _INCLUDED_GEOMETRY_
#define _INCLUDED_GEOMETRY_

#include "point.h"

#include <string>
#include <vector>

namespace geometries {

  static int geoNumber = 0;
  enum shape { POLYGON };

  class Geometry
  {
  public:
    virtual ~Geometry() {}

    virtual Point center() = 0;
    virtual shape type() const = 0;
    virtual const std::string& getName() const = 0;
    virtual const std::vector<Point*>& getPoints() const = 0;

  protected:
    std::string generateUniqueName(const std::string& name)
    {
      return name + "-" + std::to_string(++geoNumber);
    }

    Point geometryCenter(const std::vector<Point*>& points)
    {
      float x = 0;
      float y = 0;
      auto size = points.size();

      for (auto point : points)
      {
        x += point->getX();
        y += point->getY();
      }

      return Point((x / size), (y / size));
    }
  };

}

#endif

