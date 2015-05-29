#ifndef _INCLUDED_POINT_
#define _INCLUDED_POINT_

#include <vector>

namespace geometries {
  class Point3D
  {
  public:
    virtual ~Point3D();
    Point3D();
    Point3D(float x, float y, float z);
    Point3D(const Point3D& other);

    const float& getX() const;
    const float& getY() const;
    const float& getZ() const;

    const std::vector<float>& get() const;

    void translation(float dx, float dy, float dz);
    void scaling(float sx, float sy, float sz);
    
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    bool equals(const Point3D& other, float epison) const;

    bool operator==(const Point3D& other) const;
    bool operator!=(const Point3D& other) const;
    bool operator< (const Point3D& other) const;
    bool operator> (const Point3D& other) const;

    Point3D& operator=(const Point3D& other);
    Point3D& operator+=(const Point3D& other);
    Point3D& operator*=(float number);

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
