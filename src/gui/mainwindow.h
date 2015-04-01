#ifndef _INCLUDED_MAINWINDOW_H
#define _INCLUDED_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class ViewPort;
class Window;

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

private slots:
  void on_upButton_clicked();
  void on_leftButton_clicked();
  void on_downButton_clicked();
  void on_rightButton_clicked();

  void on_leftRotateButton_clicked();
  void on_rightRotateButton_clicked();

  void on_zoomInButton_clicked();
  void on_zoomOutButton_clicked();

  void on_addLineButton_clicked();

private:
  Ui::MainWindow *ui;

  std::unique_ptr<ViewPort> viewPort_;
  std::unique_ptr<Window> window_;
};

#endif // MAINWINDOW_H
