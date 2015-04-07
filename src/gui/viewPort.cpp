#include "viewPort.h"
#include "window.h"
#include "line.h"

#include <QPainter>
#include <QDebug>


ViewPort::~ViewPort()
{

}

ViewPort::ViewPort(Window *window, QWidget *parent)
    : window_(window)
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

void ViewPort::paintEvent(QPaintEvent *)
{    
    QPainter painter(this);

    for (auto geometry : window_->getGeometries()) 
    {  
      switch (geometry->type()) 
      {
        case geometries::POINT:
        {
          auto point = geometry->getPoints().at(0);
          painter.drawPoint(QPointF(point.getX(), point.getY()));
          break;
        }
        case geometries::LINE:
        {
          auto pointAtLine = geometry->getPoints();
          painter.drawLine(QPointF(pointAtLine.at(0).getX(), pointAtLine.at(0).getY()),
            QPointF(pointAtLine.at(1).getX(), pointAtLine.at(1).getY()));
          break;
        }
        case geometries::POLYGON:
        {
          QPolygonF polygonQt;
          for (auto point : geometry->getPoints())
          {
            polygonQt << QPointF(point.getX(), point.getY());
          }
          painter.drawPolygon(polygonQt);
        }
      }
      painter.restore();
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    //painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
