#ifndef _INCLUDED_GEOMETRY_
#define _INCLUDED_GEOMETRY_

#include "point.h"

#include <string>
#include <vector>

namespace geometries {

  static int geoNumber = 0;
  enum shape { POLYGON, BEZIER };

  class Geometry
  {
  public:
    virtual ~Geometry() {}

    virtual shape type() const = 0;
    virtual const std::string& getName() const = 0;
    virtual const std::vector<Point*>& getPoints() const = 0;

    Point center() const
    {
      auto points = getPoints();
      float x = 0;
      float y = 0;
      auto size = points.size();

      for (auto point : points)
      {
        x += point->getX();
        y += point->getY();
      }

      return Point((x / size), (y / size));
    };

    void translation(float dx, float dy)
    {
      for (auto &point : getPoints())
      {
        point->translation(dx, dy);
      }
    };
    
    void scaling(float sx, float sy)
    {
      auto centerGeometry = center();
      auto dx = centerGeometry.getX();
      auto dy = centerGeometry.getY();

      translation(-dx, -dy); // translate to origin by center Geometry

      for (auto point : getPoints())
      {
        point->scaling(sx, sy);
      }

      translation(dx, dy); // return to original center Geometry
    };

    void rotate(float angle)
    {
      rotate(center(), angle);
    };

    void rotate(const Point& rotatePoint, float angle)
    {
      auto dx = rotatePoint.getX();
      auto dy = rotatePoint.getY();

      translation(-dx, -dy); // translate to rotate point 

      for (auto point : getPoints())
      {
        point->rotate(angle);
      }

      translation(dx, dy); // return to original center Geometry
    };

  protected:
    std::string generateUniqueName(const std::string& name)
    {
      return name + "-" + std::to_string(++geoNumber);
    }
  };

}

#endif

