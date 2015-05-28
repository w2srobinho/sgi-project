#ifndef _INCLUDED_WINDOW_
#define _INCLUDED_WINDOW_

#include "geometry.h"
#include "point2D.h"

#include <unordered_map>
#include <memory>
#include <vector>
#include <utility>

class Window
{
public:
  ~Window();
  Window(const geometries::Point2D& min, const geometries::Point2D& max);

  std::vector<geometries::Geometry*> getGeometries() const;

  const geometries::Point2D& getMinPoint() const;
  const geometries::Point2D& getMaxPoint() const;
  
  void addGeometry(geometries::Geometry *shape);
  void verticalMove(float rate);
  void horizontalMove(float rate);
  void translateGeometry(const std::string& geometryName, float dx, float dy);
  void scalingGeometry(const std::string& geometryName, float sx, float sy);
  void rotateOrigin(const std::string& geometryName, float angle);
  void rotateWindow(const std::string& geometryName, float angle);
  void rotatePoint(const std::string& geometryName, const geometries::Point2D& rotatePoint, float angle);
  geometries::Point2D center() const;
  void zoomIn();
  void zoomOut();

private:
  void zoom(float factor);

private:
  geometries::Point2D minPoint, maxPoint;

  std::vector<geometries::Geometry*> _geometries;
  std::unordered_map<std::string, geometries::Geometry*> displayFile;
  std::vector<std::unique_ptr<geometries::Geometry>> cleanUp;
};
#endif

