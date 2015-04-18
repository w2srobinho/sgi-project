#include "conversions.h"
#include "graphicPoint.h"
#include "line.h"
#include "mainwindow.h"
#include "point.h"
#include "polygon.h"
#include "ui_mainwindow.h"
#include "viewPort.h"
#include "window.h"

#include <QIcon>
#include <QMessageBox>
#include <QString>

#include <assert.h>
#include <iostream>

namespace {
  const int RATE_TO_MOVE = 2;
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  Q_INIT_RESOURCE(images);

  ui->setupUi(this);
  connectButtons();
  
  window = std::make_unique<Window>(geometries::Point(10.0, 5.0), geometries::Point(40.0, 30.0));
  viewPort = std::make_unique<ViewPort>(window.get(), ui->groupBox);
  ui->verticalLayout_3->addWidget(viewPort.get());
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::upButton_clicked()
{
  window->verticalMove(RATE_TO_MOVE);
  viewPort->redraw();
}

void MainWindow::downButton_clicked()
{
  window->verticalMove(-RATE_TO_MOVE);
  viewPort->redraw();
}

void MainWindow::leftButton_clicked()
{
  window->horizontalMove(-RATE_TO_MOVE);
  viewPort->redraw();
}

void MainWindow::rightButton_clicked()
{
  window->horizontalMove(RATE_TO_MOVE);
  viewPort->redraw();
}

void MainWindow::leftRotateButton_clicked()
{

}

void MainWindow::rightRotateButton_clicked()
{

}

void MainWindow::zoomInButton_clicked()
{
  window->zoomIn();
  viewPort->redraw();
}

void MainWindow::zoomOutButton_clicked()
{
  window->zoomOut();
  viewPort->redraw();
}

void MainWindow::addPointButton_clicked()
{
  assert(pointsToPolygon.size() > 1);
  auto x = ui->pointEditX->text();
  auto y = ui->pointEditY->text();

  if (x.isEmpty() ||
      y.isEmpty())
  {
    showCriticalMessage("Fill in the fields correctly!");
    return;
  }

  auto name = ui->pointName->text();
  geometries::Geometry * geometry;

  if (name.isEmpty())
    geometry = new geometries::GraphicPoint(x.toFloat(), y.toFloat());
  else {
    geometry = new geometries::GraphicPoint(x.toFloat(), y.toFloat(), name.toStdString());
  }

  viewPort->addGeometry(geometry);
  ui->listWidget->addItem(QString(geometry->getName().c_str()));
}

void MainWindow::showCriticalMessage(std::string message)
{
  QMessageBox::critical(this,
                        tr("Critical"),
                        QString(message.c_str()),
                        QMessageBox::Ok);
}

void MainWindow::addLineButton_clicked()
{
  auto ptoX1 = ui->lineX1->text();
  auto ptoY1 = ui->lineY1->text();
  auto ptoX2 = ui->lineX2->text();
  auto ptoY2 = ui->lineY2->text();

  if (ptoX1.isEmpty() ||
      ptoY1.isEmpty() ||
      ptoX2.isEmpty() ||
      ptoY2.isEmpty())
  {
    showCriticalMessage("Fill in the fields correctly!");
    return;
  }

  auto name = ui->LineName->text();
  geometries::Point p1(ptoX1.toFloat(), ptoY1.toFloat());
  geometries::Point p2(ptoX2.toFloat(), ptoY2.toFloat());

  geometries::Geometry *geometry;

  if (name.isEmpty())
    geometry = new geometries::Line({ p1, p2 });
  else
    geometry = new geometries::Line(p1, p2, name.toStdString());

  viewPort->addGeometry(geometry);
  ui->listWidget->addItem(QString(geometry->getName().c_str()));
}


void MainWindow::addPointOnPolygonButton_clicked()
{
  auto x = ui->polygonEditX->text();
  auto y = ui->polygonEditY->text();

  if (x.isEmpty() ||
      y.isEmpty())
  {
    showCriticalMessage("Add the X and Y coordinates,\nto add the point to Polygon!");
    return;
  }

  pointsToPolygon.push_back(geometries::Point(x.toFloat(), y.toFloat()));
  ui->polygonEditX->setText("");
  ui->polygonEditY->setText("");
}


void MainWindow::addPolygonButton_clicked()
{
  if (!ui->polygonEditX->text().isEmpty())
    addPointOnPolygonButton_clicked();

  auto name = ui->polygonName->text();
  geometries::Geometry * geometry;

  if (name.isEmpty())
    geometry = new geometries::Polygon(pointsToPolygon);
  else
    geometry = new geometries::Polygon(pointsToPolygon, name.toStdString());

  assert(pointsToPolygon.size() > 1);
  viewPort->addGeometry(geometry);
  ui->listWidget->addItem(QString(geometry->getName().c_str()));
  pointsToPolygon.clear();
}

void MainWindow::connectButtons()
{
  ui->rotateEdit->setEnabled(false);
  connect(ui->addPointButton, &QPushButton::clicked,
    this, &MainWindow::addPointButton_clicked);
  connect(ui->addLineButton, &QPushButton::clicked,
    this, &MainWindow::addLineButton_clicked);
  connect(ui->addPointOnPolygonButton, &QPushButton::clicked,
    this, &MainWindow::addPointOnPolygonButton_clicked);
  connect(ui->addPolygonButton, &QPushButton::clicked,
    this, &MainWindow::addPolygonButton_clicked);
  connect(ui->zoomInButton, &QPushButton::clicked,
    this, &MainWindow::zoomInButton_clicked);
  connect(ui->zoomOutButton, &QPushButton::clicked,
    this, &MainWindow::zoomOutButton_clicked);
  connect(ui->upButton, &QPushButton::clicked,
    this, &MainWindow::upButton_clicked);
  connect(ui->downButton, &QPushButton::clicked,
    this, &MainWindow::downButton_clicked);
  connect(ui->leftButton, &QPushButton::clicked,
    this, &MainWindow::leftButton_clicked);
  connect(ui->rightButton, &QPushButton::clicked,
    this, &MainWindow::rightButton_clicked);
}
