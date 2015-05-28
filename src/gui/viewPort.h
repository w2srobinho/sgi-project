#ifndef _INCLUDED_VIEWPORT_
#define _INCLUDED_VIEWPORT_

#include <QWidget>
#include "point2D.h"

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
  
  geometries::Point2D windowToViewport(const geometries::Point2D& pointOnWindow);

  void addGeometry(geometries::Geometry *geometry);
  void redraw();

protected:
  void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
  void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
  Window *_window;

  geometries::Point2D minVpPoint, maxVpPoint;
};

#endif
