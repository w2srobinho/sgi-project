#include "viewPort.h"
#include "window.h"
#include "line.h"

#include <QPainter>
#include <QResizeEvent>

namespace {
  const int OFFSET_TO_VP = 10;
}

ViewPort::~ViewPort()
{

}

ViewPort::ViewPort(Window *window, QWidget *parent)
    : QWidget(parent)
    , window_(window)
    , minVpPoint(geometries::Point(0, 0))
    , maxVpPoint(geometries::Point(0, 0))
{
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);    
}

QSize ViewPort::minimumSizeHint() const
{
    return QSize(300, 250);
}

QSize ViewPort::sizeHint() const
{
    return QSize(400, 200);
}

geometries::Point ViewPort::windowToViewport(const geometries::Point& pointOnWindow)
{
  /**
  * Xvp = ((Xw - Xwmin) / (Xwmax - Xwmin)) * (Xvpmax - Xvpmin)
  */
  auto windowWidth = window_->getMaxPoint().getX() - window_->getMinPoint().getX();
  auto viewPortWidth = width()/*maxVpPoint.getX() - minVpPoint.getX()*/;
  auto xvp = ((pointOnWindow.getX() - window_->getMinPoint().getX()) / (windowWidth)) * viewPortWidth;

  /**
  * Yvp = (1 - ((Yw - Ywmin) / (Ywmax - Ywmin))) * (Yvpmax - Yvpmin)
  */
  auto windowHeight = window_->getMaxPoint().getY() - window_->getMinPoint().getY();
  auto viewPortHeight = height()/*maxVpPoint.getY() - minVpPoint.getY()*/;
  auto yvp = (1 - ((pointOnWindow.getY() - window_->getMinPoint().getY()) / (windowHeight))) * viewPortHeight;

  return geometries::Point(xvp, yvp);
}

void ViewPort::addGeometry(geometries::Geometry *geometry)
{
    window_->addGeometry(geometry);
    update();
}

void ViewPort::resizeEvent(QResizeEvent *e)
{
  minVpPoint.setX(x() + OFFSET_TO_VP);
  minVpPoint.setY(y() - OFFSET_TO_VP);
  maxVpPoint.setX(e->size().width() - OFFSET_TO_VP);
  maxVpPoint.setY(e->size().height() - OFFSET_TO_VP);
  update();
  QWidget::resizeEvent(e);
}

void ViewPort::paintEvent(QPaintEvent *)
{    
    QPainter painter(this);
    
    for (auto geometry : window_->getGeometries()) 
    {  
      switch (geometry->type()) 
      {
        case geometries::POINT:
        {
          auto point = windowToViewport(geometry->getPoints().at(0));
          painter.drawPoint(QPointF(point.getX(), point.getY()));
          break;
        }
        case geometries::LINE:
        {
          auto pointAtLine = geometry->getPoints();
          auto p0 = windowToViewport(pointAtLine.at(0));
          auto p1 = windowToViewport(pointAtLine.at(1));

          painter.drawLine(QPointF(p0.getX(), p0.getY()), QPointF(p1.getX(), p1.getY()));
          break;
        }
        case geometries::POLYGON:
        {
          QPolygonF polygonQt;
          for (auto point : geometry->getPoints())
          {
            auto vpPoint = windowToViewport(point);
            polygonQt << QPointF(vpPoint.getX(), vpPoint.getY());
          }
          painter.drawPolygon(polygonQt);
        }
      }
      painter.restore();
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);

    QPointF topLeft(minVpPoint.getX(), minVpPoint.getY());
    QPointF bottomRight(maxVpPoint.getX(), maxVpPoint.getY());

    painter.drawRect(QRectF(topLeft, bottomRight));
}

void ViewPort::redraw()
{
  update();
}
