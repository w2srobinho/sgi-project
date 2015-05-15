#include "clipping.h"

clipping::CohenSutherland::CohenSutherland(
  const geometries::Point& minPoint, 
  const geometries::Point& maxPoint
)
  : _minPoint(minPoint)
  , _maxPoint(maxPoint)
{

}

std::vector<geometries::Point> clipping::CohenSutherland::lineClip(
  const geometries::Point& p0,
  const geometries::Point& p1)
{
  float x0 = p0.getX();
  float y0 = p0.getY();
  float x1 = p1.getX();
  float y1 = p1.getY();

  int outcode0 = computeOutCode(x0, y0);
  int outcode1 = computeOutCode(x1, y1);
  
  while (true)
  {
    if (!(outcode0 | outcode1))
      return { geometries::Point(x0, y0), geometries::Point(x1, y1) };
    else if (outcode0 & outcode1)
      return { geometries::Point(0, 0), geometries::Point(0, 0) };
    else
    {
      float x = 0;
      float y = 0;

      int outcodeOut = outcode0 ? outcode0 : outcode1;

      if (outcodeOut & TOP)
      {
        float yTop = _maxPoint.getY();
        x = ((x1 - x0) / (y1 - y0)) * (yTop - y0) + x0;
        y = yTop;
      }
      else if (outcodeOut & BOTTOM)
      {
        float yBottom = _minPoint.getY();
        x = ((x1 - x0) / (y1 - y0)) * (yBottom - y0) + x0;
        y = yBottom;
      }
      else if (outcodeOut & RIGHT) 
      {
        float xRight = _maxPoint.getX();
        y = ((y1 - y0) / (x1 - x0)) * (xRight - x0) + y0;
        x = xRight;
      }
      else if (outcodeOut & LEFT) 
      {
        float xLeft = _minPoint.getX();
        y = ((y1 - y0) / (x1 - x0)) * (xLeft - x0) + y0;
        x = xLeft;
      }

      if (outcodeOut == outcode0) 
      {
        x0 = x;
        y0 = y;
        outcode0 = computeOutCode(x0, y0);
      }
      else 
      {
        x1 = x;
        y1 = y;
        outcode1 = computeOutCode(x1, y1);
      }
    }
  }

  return { geometries::Point(x0, y0), geometries::Point(x1, y1) };
}

std::vector<geometries::Point> clipping::CohenSutherland::polygonClip(
  const std::vector<geometries::Point> &polygon)
{
  std::vector<geometries::Point> polygonClipped;
  auto previusPoint = polygon[0];

  for (unsigned int i = 1; i < polygon.size(); ++i)
  {
    auto lineClipped = lineClip(previusPoint, polygon[i]);
    previusPoint = polygon[i];

    auto p0Clipped = lineClipped.at(0);
    auto p1Clipped = lineClipped.at(1);
    if (p0Clipped != p1Clipped)
    {
      polygonClipped.push_back(p0Clipped);
      polygonClipped.push_back(p1Clipped);
    }
  }

  return polygonClipped;
}

int clipping::CohenSutherland::computeOutCode(float x, float y)
{
  int code = INSIDE;

  if (x < _minPoint.getX())           // to the left of clip window
    code |= LEFT;
  else if (x > _maxPoint.getX())      // to the right of clip window
    code |= RIGHT;
  if (y < _minPoint.getY())           // below the clip window
    code |= BOTTOM;
  else if (y > _maxPoint.getY())      // above the clip window
    code |= TOP;

  return code;
}
