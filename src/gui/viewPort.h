#ifndef _INCLUDED_VIEWPORT_
#define _INCLUDED_VIEWPORT_

#include <QWidget>

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

    void addGeometry(geometries::Geometry *geometry);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Window *window_;
};

#endif
