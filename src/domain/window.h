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
  Window(const geometries::Point& min, const geometries::Point& max);

  std::vector<geometries::Geometry*> getGeometries() const;
  std::pair<geometries::Point, geometries::Point> getWindowPoints() const;

  geometries::Point toViewPort(
    const geometries::Point& pointOnWindow,
    const geometries::Point& vpMinPoint,
    const geometries::Point& vpMaxPoint);
  
  void addGeometry(geometries::Geometry *shape);
  void verticalMove(float rate);
  void horizontalMove(float rate);
  void zoomIn();
  void zoomOut();

private:
  void zoom(float factor);

private:
  geometries::Point minPoint, maxPoint;

  std::vector<geometries::Geometry*> geometries_;
  std::unordered_map<std::string, geometries::Geometry*> displayFile;
  std::vector<std::unique_ptr<geometries::Geometry>> cleanUp;
};
#endif

