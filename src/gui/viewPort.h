#ifndef _INCLUDED_VIEWPORT_
#define _INCLUDED_VIEWPORT_

#include <QWidget>
#include "point.h"

class Window;

namespace geometries {
  class Geometry;
}

class ViewPort : public QWidget
{
  Q_OBJECT

public:
  ViewPort(Window *window, QWidget *parent = nullptr);
  ~ViewPort();

  QSize minimumSizeHint() const Q_DECL_OVERRIDE;
  QSize sizeHint() const Q_DECL_OVERRIDE;
  
  geometries::Point windowToViewport(const geometries::Point& pointOnWindow);

  void addGeometry(geometries::Geometry *geometry);
  void redraw();

protected:
  void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
  void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
  Window *window_;

  geometries::Point minVpPoint, maxVpPoint;
};

#endif
