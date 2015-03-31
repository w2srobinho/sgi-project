#ifndef _INCLUDED_POINT_
#define _INCLUDED_POINT_

namespace geometries {
  class Point
  {
  public:
    ~Point();
    Point(const float& x, const float& y);
    Point(const Point& other);

    const float& getX() const;
    const float& getY() const;

    Point& operator=(const Point& other);

  private:
    float x;
    float y;
  };
}
#endif
