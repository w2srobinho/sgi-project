#ifndef _INCLUDED_VIEWPORT_
#define _INCLUDED_VIEWPORT_

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

namespace geometries {
  class Geometry;
}

class ViewPort : public QWidget
{
    Q_OBJECT

public:
    ViewPort(QWidget *parent = nullptr);
    ~ViewPort();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void addGeometry(geometries::Geometry *geometry);

public slots:
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
};

#endif
