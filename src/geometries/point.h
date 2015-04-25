#ifndef _INCLUDED_POINT_
#define _INCLUDED_POINT_

#include <vector>

namespace geometries {
  class Point
  {
  public:
    virtual ~Point();
    Point();
    Point(std::vector<float> point);
    Point(float x, float y);
    Point(const Point& other);

    const float& getX() const;
    const float& getY() const;
    const float& getZ() const;

    std::vector<float> get() const;

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);

    bool equals(const Point& other, float epison) const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    bool operator< (const Point& other) const;
    bool operator> (const Point& other) const;

    Point& operator=(const Point& other);
    Point& operator*=(float number);

  private:
    float x_, y_, z_;
  };
}


#endif
