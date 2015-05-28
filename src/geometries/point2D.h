#ifndef _INCLUDED_POINT_
#define _INCLUDED_POINT_

#include <vector>

namespace geometries {
  class Point2D
  {
  public:
    virtual ~Point2D();
    Point2D();
    Point2D(float x, float y);
    Point2D(const Point2D& other);

    const float& getX() const;
    const float& getY() const;

    const std::vector<float>& get() const;

    void translation(float dx, float dy);
    void scaling(float sx, float sy);
    void rotate(float angle);

    bool equals(const Point2D& other, float epison) const;

    bool operator==(const Point2D& other) const;
    bool operator!=(const Point2D& other) const;
    bool operator< (const Point2D& other) const;
    bool operator> (const Point2D& other) const;

    Point2D& operator=(const Point2D& other);
    Point2D& operator+=(const Point2D& other);
    Point2D& operator*=(float number);

  private:
    std::vector<float> dotProduct(
      const std::vector<float>& _vector,
      const std::vector<std::vector<float>>& _matrix);

  private:
    std::vector<float> _point;
  };
}


#endif
