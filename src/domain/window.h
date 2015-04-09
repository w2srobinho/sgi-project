#ifndef _INCLUDED_WINDOW_
#define _INCLUDED_WINDOW_

#include "geometry.h"
#include "point.h"

#include <unordered_map>
#include <memory>
#include <vector>
#include <utility>

class Window
{
public:
  ~Window();
  Window(float width, float height);

  std::vector<geometries::Geometry*> getGeometries() const;
  std::pair<float, float> getWindowSize() const;
  std::pair<geometries::Point, geometries::Point> getWindowPoints() const;

  void addGeometry(geometries::Geometry *shape);
  void zoomIn();
  void zoomOut();

  float getActualAmount() const;

private:
  void zoom(float factor);

private:
  float width_;
  float height_;
  float defaultWidth;

  std::vector<geometries::Geometry*> geometries_;
  std::unordered_map<std::string, geometries::Geometry*> displayFile;
  std::vector<std::unique_ptr<geometries::Geometry>> cleanUp;
};

#endif

