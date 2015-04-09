#ifndef _INCLUDED_GRAPHICPOINT_
#define _INCLUDED_GRAPHICPOINT_

#include "point.h"
#include "geometry.h"

#include <vector>

namespace geometries {
  class GraphicPoint 
    : public Geometry
    , public Point
  {
  public:
    ~GraphicPoint();
    GraphicPoint(float x, float y);
    GraphicPoint(float x, float y, const std::string& name);

    Point center() override;

    std::vector<Point> getPoints() const override;
    const std::string& getName() const override;

    shape type() const override;


  private:
    std::string name_;
  };
}

#endif
