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
    //antialiased = false;
    //transformed = false;
    //pixmap.load(":/images/qt-logo.png");

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

/*
void ViewPort::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}

void ViewPort::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

void ViewPort::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

void ViewPort::setTransformed(bool transformed)
{
    this->transformed = transformed;
    update();
}
*/
void ViewPort::paintEvent(QPaintEvent *)
{    
    QPainter painter(this);
    //painter.setPen(pen);
    //painter.setBrush(brush);
    //if (antialiased)
    //    painter.setRenderHint(QPainter::Antialiasing, true);
    qDebug() << "antes do looping";
    //auto vectorPoints =
    for (auto it : window_->getGeometries()) {
      qDebug() << "pós looping";
      if (it->type() == geometries::LINE) {
        qDebug() << "pós if";

//        auto& line = ;
        //painter.drawLine(QPointF(it->getPoints().at(0).getX(), it->getPoints().at(0).getY()),
        //                 QPointF(it->getPoints().at(1).getX(), it->getPoints().at(1).getY()));
      }
      //switch (geometry->type()) {
      //  qDebug() << "switch geometry type: " << geometry->type();
      //  case geometries::LINE:
      //    auto& line = geometry.getPoints();
      //
      //    //painter.drawLine(QPointF(line.at(0).getX(), line.at(0).getY()),
      //    //                 QPointF(line.at(1).getX(), line.at(1).getY()));
      //    break;
      //  //default:
      //  //  break;
      //}
     // painter.restore();
    }
//        for (int y = 0; y < height(); y += 100) {
//            painter.save();
//            painter.translate(x, y);
//
//            if (transformed) {
//                painter.translate(50, 50);
//                painter.rotate(60.0);
//                painter.scale(0.6, 0.9);
//                painter.translate(-50, -50);
//            }
//
//            switch (shape) {
//            case Line:
//                painter.drawLine(rect.bottomLeft(), rect.topRight());
//                break;
//            case Points:
//                painter.drawPoints(points, 4);
//                break;
//            case Polyline:
//                painter.drawPolyline(points, 4);
//                break;
//            case Polygon:
//                painter.drawPolygon(points, 4);
//                break;
//            case Rect:
//                painter.drawRect(rect);
//                break;
//            case RoundedRect:
//                painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
//                break;
//            case Ellipse:
//                painter.drawEllipse(rect);
//                break;
//            case Arc:
//                painter.drawArc(rect, startAngle, arcLength);
//                break;
//            case Chord:
//                painter.drawChord(rect, startAngle, arcLength);
//                break;
//            case Pie:
//                painter.drawPie(rect, startAngle, arcLength);
//                break;
//            case Path:
//                painter.drawPath(path);
//                break;
//            case Text:
//                painter.drawText(rect, Qt::AlignCenter, tr("Qt by\nDigia"));
//                break;
//            case Pixmap:
//                painter.drawPixmap(10, 10, pixmap);
//            }
//            painter.restore();
//        }
//    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
