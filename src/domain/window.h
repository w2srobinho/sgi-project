#ifndef _INCLUDED_WINDOW_
#define _INCLUDED_WINDOW_

#include "geometry.h"

#include <memory>
#include <vector>
#include <utility>

class Window
{
public:
  ~Window();
  Window();

  void addGeometry(geometries::Geometry *shape);

  std::vector<geometries::Geometry*> getGeometries() const;

  void setWindowSize(float width, float height);
  std::pair<float, float> getWindowSize() const;

  void resetDefaultSize();


private:
  float width_;
  float height_;

  std::vector<geometries::Geometry*> geometries_;
  std::vector<std::unique_ptr<geometries::Geometry>> cleanUp;
};

#endif

