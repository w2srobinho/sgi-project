#ifndef _INCLUDED_WINDOW_
#define _INCLUDED_WINDOW_

#include "geometry.h"

#include <memory>
#include <vector>

class Window
{
public:
  ~Window();
  Window(float width, float height);

  void addGeometry(geometries::Geometry *shape);

  std::vector<geometries::Geometry*> getGeometries() const;

private:
  float width_;
  float height_;

  std::vector<geometries::Geometry*> geometries_;
  std::vector<std::unique_ptr<geometries::Geometry>> cleanUp;
};

#endif

