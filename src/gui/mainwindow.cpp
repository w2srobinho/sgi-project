#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::configureResources()
{
  // ui->upButton->setIcon(QIcon(QPixmap(":/resources/navigate_up_24.png")));

  // QIcon downIcon;
  // downIcon.addFile(
  //       QStringLiteral(":/resources/navigate_down_24.png"), QSize(), QIcon::Normal, QIcon::Off);
  // ui->downButton->setIcon(downIcon);
  //
  // QIcon leftIcon;
  // leftIcon.addFile(
  //       QStringLiteral(":/resources/navigate_left_24.png"), QSize(), QIcon::Normal, QIcon::Off);
  // ui->leftButton->setIcon(leftIcon);
  //
  // QIcon rightIcon;
  // rightIcon.addFile(
  //       QStringLiteral(":/resources/navigate_right_24.png"), QSize(), QIcon::Normal, QIcon::Off);
  // ui->rightButton->setIcon(rightIcon);
  //
  // QIcon leftRotateIcon;
  // leftRotateIcon.addFile(
  //       QStringLiteral(":/resources/rotate_left.png"), QSize(), QIcon::Normal, QIcon::Off);
  // ui->leftRotateButton->setIcon(leftRotateIcon);
}
