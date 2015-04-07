#ifndef _INCLUDED_POINT_
#define _INCLUDED_POINT_

namespace geometries {
  class Point
  {
  public:
    virtual ~Point();
    Point(float x, float y);
    Point(const Point& other);

    const float& getX() const;
    const float& getY() const;
    const float& getZ() const;

    Point& operator=(const Point& other);

  private:
    float x_;
    float y_;
    float z_;
  };
}

#endif
