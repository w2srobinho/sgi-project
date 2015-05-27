#include "viewPort.h"

#include "bezier.h"
#include "clipping.h"
#include "line.h"
#include "window.h"

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
    , _window(window)
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
  auto windowWidth = _window->getMaxPoint().getX() - _window->getMinPoint().getX();
  auto viewPortWidth = width()/*maxVpPoint.getX() - minVpPoint.getX()*/;
  auto xvp = ((pointOnWindow.getX() - _window->getMinPoint().getX()) / (windowWidth)) * viewPortWidth;

  /**
  * Yvp = (1 - ((Yw - Ywmin) / (Ywmax - Ywmin))) * (Yvpmax - Yvpmin)
  */
  auto windowHeight = _window->getMaxPoint().getY() - _window->getMinPoint().getY();
  auto viewPortHeight = height()/*maxVpPoint.getY() - minVpPoint.getY()*/;
  auto yvp = (1 - ((pointOnWindow.getY() - _window->getMinPoint().getY()) / (windowHeight))) * viewPortHeight;

  return geometries::Point(xvp, yvp);
}

void ViewPort::addGeometry(geometries::Geometry *geometry)
{
    _window->addGeometry(geometry);
    update();
}

void ViewPort::resizeEvent(QResizeEvent *e)
{
  minVpPoint = geometries::Point(x() + OFFSET_TO_VP, y() - OFFSET_TO_VP);
  maxVpPoint = geometries::Point(e->size().width() - OFFSET_TO_VP, e->size().height() - OFFSET_TO_VP);
  update();
  QWidget::resizeEvent(e);
}

void ViewPort::paintEvent(QPaintEvent *)
{    
    QPainter painter(this);
    
    clipping::Clip sutherland(minVpPoint, maxVpPoint);

    for (auto geometry : _window->getGeometries()) 
    {  
      switch (geometry->type())
      {
        case geometries::POLYGON:
        {
          switch (geometry->getPoints().size())
          {
            case 1:
            {
              auto point = windowToViewport(*geometry->getPoints().at(0));
              painter.drawPoint(QPointF(point.getX(), point.getY()));
              break;
            }
            case 2:
            {
              auto pointAtLine = geometry->getPoints();
              auto p0 = windowToViewport(*pointAtLine.at(0));
              auto p1 = windowToViewport(*pointAtLine.at(1));


              auto lineClipped = sutherland.cSutherlandLine(p0, p1);
              auto p0Clipped = lineClipped.at(0);
              auto p1Clipped = lineClipped.at(1);
              if (p0Clipped != p1Clipped)
              {
                painter.drawLine(
                  QPointF(p0Clipped.getX(), p0Clipped.getY()),
                  QPointF(p1Clipped.getX(), p1Clipped.getY()));
              }
              break;
            }
            default:
            {
              QPolygonF polygonQt;
              std::vector<geometries::Point> polygonTransformed;

              for (auto point : geometry->getPoints())
                polygonTransformed.push_back(windowToViewport(*point));

              if (polygonTransformed.front() != polygonTransformed.back())
              {
                for (std::size_t i = 1; i < polygonTransformed.size(); ++i)
                {
                  auto clipped = sutherland.lBarskyLine(polygonTransformed[i - 1], polygonTransformed[i]);
                  QPointF from(clipped[0].getX(), clipped[0].getY());
                  QPointF to(clipped[1].getX(), clipped[1].getY());
                  painter.drawLine(from, to);
                }
              }
              else
              {
                auto polygonClipped = sutherland.lBarskyPolygon(polygonTransformed);

                for (auto point : polygonClipped)
                  polygonQt << QPointF(point.getX(), point.getY());

                painter.setBrush(QBrush(QColor(128, 128, 255, 128)));
                painter.drawPolygon(polygonQt);
              }
              break;
            }
          }
        }
        case geometries::BEZIER:
        {
          auto bezier = dynamic_cast<geometries::Bezier*>(geometry);
          if (!bezier)
            break;

          QList<QPointF> listPointQt;
          std::vector<geometries::Point> bezierTransformed;
          
          for (auto point : bezier->getBezierPoints(1u))
            bezierTransformed.push_back(windowToViewport(point));

          for (std::size_t i = 1; i < bezierTransformed.size(); ++i)
          {
            auto clipped = sutherland.lBarskyLine(bezierTransformed[i - 1], bezierTransformed[i]);
            QPointF from(clipped[0].getX(), clipped[0].getY());
            QPointF to(clipped[1].getX(), clipped[1].getY());
            painter.drawLine(from, to);
          }
          break;
        }
      }
      painter.restore();
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);

    QPointF topLeft(minVpPoint.getX()-1, minVpPoint.getY()-1);
    QPointF bottomRight(maxVpPoint.getX(), maxVpPoint.getY()+1);

    painter.drawRect(QRectF(topLeft, bottomRight));
}

void ViewPort::redraw()
{
  update();
}
