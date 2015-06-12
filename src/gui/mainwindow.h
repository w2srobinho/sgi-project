#ifndef _INCLUDED_MAINWINDOW_
#define _INCLUDED_MAINWINDOW_

#include <QMainWindow>
#include <memory>
#include <vector>

class ViewPort;
class Window;

namespace geometries
{
  class Point;
}

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();


private:
  void showCriticalMessage(std::string message);
  void connectButtons();
  void hasNotGeometry();
  void haveGeometry();

protected slots:
  void upButton_clicked();
  void leftButton_clicked();
  void downButton_clicked();
  void rightButton_clicked();

  void leftRotateButton_clicked();
  void rightRotateButton_clicked();

  void zoomInButton_clicked();
  void zoomOutButton_clicked();

  void addPointButton_clicked();
  void addLineButton_clicked();
  void addPointOnPolygonButton_clicked();
  void addPolygonButton_clicked();
  void addCurveButton_clicked();

  void applyTranslate_clicked();
  void applyScaling_clicked();
 
private:
  void rotate(float angle);

private:
  Ui::MainWindow *ui;

  std::unique_ptr<ViewPort> viewPort;
  std::unique_ptr<Window> window;

  std::vector<geometries::Point*> pointsToPolygon;
};

#endif
