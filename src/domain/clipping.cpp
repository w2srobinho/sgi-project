#include "clipping.h"

clipping::CohenSutherland::CohenSutherland(
  const geometries::Point& minPoint, 
  const geometries::Point& maxPoint
)
  : _minPoint(minPoint)
  , _maxPoint(maxPoint)
{

}

std::vector<geometries::Point> clipping::CohenSutherland::LineClip(
  const geometries::Point& p0,
  const geometries::Point& p1)
{
  float x0 = p0.getX();
  float y0 = p0.getY();
  float x1 = p1.getX();
  float y1 = p1.getY();

  int outcode0 = computeOutCode(x0, y0);
  int outcode1 = computeOutCode(x1, y1);

  std::vector<geometries::Point> line;
  while (true)
  {
    if (!(outcode0 | outcode1))
    {
      line = { p0, p1 };
      break;
    }

    if (outcode0 & outcode1)
      break;

    float x = 0;
    float y = 0;

    int outcodeOut = outcode0 ? outcode0 : outcode1;

    if (outcodeOut & TOP)
    {
      float ymax = _maxPoint.getY();
      x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
      y = ymax;
    }
    else if (outcodeOut & BOTTOM)
    {
      float ymin = _minPoint.getY();
      x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
      y = ymin;
    }
    else if (outcodeOut & RIGHT) {
      float xmax = _maxPoint.getX();
      y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
      x = xmax;
    }
    else if (outcodeOut & LEFT) {
      float xmin = _minPoint.getX();
      y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
      x = xmin;
    }

    if (outcodeOut == outcode0) {
      x0 = x;
      y0 = y;
      outcode0 = computeOutCode(x0, y0);
    }
    else {
      x1 = x;
      y1 = y;
      outcode1 = computeOutCode(x1, y1);
    }
  }

  return line = { geometries::Point(x0, y0), geometries::Point(x1, y1) };
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
