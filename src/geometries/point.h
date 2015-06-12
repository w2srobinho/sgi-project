#ifndef _INCLUDED_POINT_
#define _INCLUDED_POINT_

#include <vector>

namespace geometries {
  class Point
  {
  public:
    virtual ~Point();
    Point();
    Point(float x, float y);
    Point(float x, float y, float z);
    Point(const Point& other);

    const float& getX() const;
    const float& getY() const;
    const float& getZ() const;

    const std::vector<float>& get() const;

    void translation(float dx, float dy, float dz);
    void scaling(float sx, float sy, float sz);
    
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    bool equals(const Point& other, float epison) const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    bool operator< (const Point& other) const;
    bool operator> (const Point& other) const;

    Point& operator=(const Point& other);
    Point& operator+=(const Point& other);
    Point& operator*=(float number);

    Point operator+ (const Point& other);

  private:
    float radiansAngle(float angle);

    std::vector<float> dotProduct(
      const std::vector<float>& _vector,
      const std::vector<std::vector<float>>& _matrix);

  private:
    std::vector<float> _point;
  };
}


#endif
