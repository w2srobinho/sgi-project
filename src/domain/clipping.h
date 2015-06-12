#pragma once
#ifndef _INCLUDED_CLIPPING_H_
#define _INCLUDED_CLIPPING_H_

#include "point.h"
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
    Clip(const geometries::Point& minPoint, const geometries::Point& maxPoint);

    std::vector<geometries::Point> cSutherlandLine(
      const geometries::Point& p0,
      const geometries::Point& p1);

    std::vector<geometries::Point> cSutherlandPolygon(
      const std::vector<geometries::Point> &polygon);

    std::vector<geometries::Point> lBarskyLine(
      const geometries::Point& p0,
      const geometries::Point& p1);

    std::vector<geometries::Point> lBarskyPolygon(
      const std::vector<geometries::Point> &polygon);

  private:
    int computeOutCode(float x, float y);

  private:
    geometries::Point _minPoint;
    geometries::Point _maxPoint;
  };
}
#endif
