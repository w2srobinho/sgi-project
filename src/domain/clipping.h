#pragma once
#ifndef _INCLUDED_CLIPPING_H_
#define _INCLUDED_CLIPPING_H_
#include "polygon.h"

namespace clipping
{
  class Clip
  {
  private:
    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000

  public:
    Clip(const geometries::Point2D& minPoint, const geometries::Point2D& maxPoint);

    std::vector<geometries::Point2D> cSutherlandLine(
      const geometries::Point2D& p0,
      const geometries::Point2D& p1);

    std::vector<geometries::Point2D> cSutherlandPolygon(
      const std::vector<geometries::Point2D> &polygon);

    std::vector<geometries::Point2D> lBarskyLine(
      const geometries::Point2D& p0,
      const geometries::Point2D& p1);

    std::vector<geometries::Point2D> lBarskyPolygon(
      const std::vector<geometries::Point2D> &polygon);

  private:
    int computeOutCode(float x, float y);

  private:
    geometries::Point2D _minPoint;
    geometries::Point2D _maxPoint;
  };
}
#endif
