#include "viewPort.h"
#include "window.h"
#include "line.h"

#include <QPainter>
#include <QDebug>

namespace {
  const int OFFSET_X_TO_VP = 10;
}

ViewPort::~ViewPort()
{

}

ViewPort::ViewPort(Window *window, QWidget *parent)
    : window_(window)
    , minVpPoint(x() + OFFSET_X_TO_VP, y())
    , maxVpPoint(geometry().bottomRight().x(), geometry().bottomRight().y())
    , QWidget(parent)
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

void ViewPort::addGeometry(geometries::Geometry *geometry)
{
    window_->addGeometry(geometry);
    update();
}

void ViewPort::resizeEvent(QResizeEvent *e)
{
  QWidget::resizeEvent(e);
  minVpPoint = geometries::Point(x() + OFFSET_X_TO_VP, y());
  maxVpPoint = geometries::Point(geometry().bottomRight().x(), geometry().bottomRight().y());
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
          auto point = window_->toViewPort(geometry->getPoints().at(0), minVpPoint, maxVpPoint);
          painter.drawPoint(QPointF(point.getX(), point.getY()));
          break;
        }
        case geometries::LINE:
        {
          auto pointAtLine = geometry->getPoints();
          auto p0 = window_->toViewPort(pointAtLine.at(0), minVpPoint, maxVpPoint);
          auto p1 = window_->toViewPort(pointAtLine.at(1), minVpPoint, maxVpPoint);

          painter.drawLine(QPointF(p0.getX(), p0.getY()), QPointF(p1.getX(), p1.getY()));
          break;
        }
        case geometries::POLYGON:
        {
          QPolygonF polygonQt;
          for (auto point : geometry->getPoints())
          {
            auto vpPoint = window_->toViewPort(point, minVpPoint, maxVpPoint);
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
    painter.drawRect(QRectF(minVpPoint.getX(), minVpPoint.getY(), maxVpPoint.getX(), maxVpPoint.getY()));
}

void ViewPort::redraw()
{
  update();
}
