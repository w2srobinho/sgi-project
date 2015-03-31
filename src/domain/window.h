#ifndef _INCLUDED_WINDOW_
#define _INCLUDED_WINDOW_

#include "geometry.h"

#include <vector>

class Window
{
public:
  ~Window();
  Window(float width, float height);

  void addGeometry(geometries::Geometry *element);

private:
  float width;
  float height;

  std::vector<geometries::Geometry *> geometries;
};

#endif

