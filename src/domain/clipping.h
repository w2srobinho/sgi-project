#pragma once
#ifndef _INCLUDED_CLIPPING_H_
#define _INCLUDED_CLIPPING_H_
#include "polygon.h"

namespace clipping
{

  class CohenSutherland
  {
  private:
    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000

  public:
    CohenSutherland(const geometries::Point& minPoint, const geometries::Point& maxPoint);

    std::vector<geometries::Point> lineClip(
      const geometries::Point& p0,
      const geometries::Point& p1);

    std::vector<geometries::Point> polygonClip(const std::vector<geometries::Point> &polygon);

  private:
    int computeOutCode(float x, float y);

  private:
    geometries::Point _minPoint;
    geometries::Point _maxPoint;
  };
}
#endif
