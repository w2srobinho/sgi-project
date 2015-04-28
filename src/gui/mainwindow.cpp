#include "conversions.h"
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
  ui->rotatePointX->setEnabled(false);
  ui->rotatePointY->setEnabled(false);
  ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  hasNotGeometry();
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
  float angle = ui->angleSpinBox->text().toFloat();
  auto currentItem = ui->listWidget->currentItem();   

  if (!currentItem)
    return;
  
  auto geometryName = currentItem->text().toStdString();

  if (ui->rb_origin->isChecked())
  {
    window->rotateOrigin(geometryName, angle);
  }
  else if (ui->rb_world->isChecked())
  {
    window->rotateWindow(geometryName, angle);
  }
  else
  {
    float rotateX = ui->rotatePointX->text().toFloat();
    float rotateY = ui->rotatePointY->text().toFloat();
    window->rotatePoint(geometryName, geometries::Point(rotateX, rotateY), angle);
  }
  viewPort->redraw();
}

void MainWindow::rightRotateButton_clicked()
{
  float angle = 360.f - ui->angleSpinBox->text().toFloat();
  auto geometryName = ui->listWidget->currentItem()->text().toStdString();

  if (ui->rb_origin->isChecked())
  {
    window->rotateOrigin(geometryName, angle);
  }
  else if (ui->rb_world->isChecked())
  {
    window->rotateWindow(geometryName, angle);
  }
  else
  {
    float rotateX = ui->rotatePointX->text().toFloat();
    float rotateY = ui->rotatePointY->text().toFloat();
    window->rotatePoint(geometryName, geometries::Point(rotateX, rotateY), angle);
  }
  viewPort->redraw();
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
  auto x = ui->pointEditX->text();
  auto y = ui->pointEditY->text();

  if (x.isEmpty() ||
      y.isEmpty())
  {
    showCriticalMessage("Fill in the fields correctly!");
    return;
  }

  auto name = ui->pointName->text().toStdString();

  geometries::Geometry * geometry;
  geometries::Point point(x.toFloat(), y.toFloat());

  if (name.empty())
    geometry = new geometries::Polygon(std::vector<geometries::Point>{point});
  else {
    geometry = new geometries::Polygon(std::vector<geometries::Point>{point}, name);
  }

  viewPort->addGeometry(geometry);
  ui->listWidget->addItem(QString(geometry->getName().c_str()));
  
  haveGeometry();
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

  auto name = ui->LineName->text().toStdString();
  geometries::Point p1(ptoX1.toFloat(), ptoY1.toFloat());
  geometries::Point p2(ptoX2.toFloat(), ptoY2.toFloat());

  geometries::Geometry *geometry;

  if (name.empty())
    geometry = new geometries::Line(std::vector<geometries::Point>{ p1, p2 });
  else
    geometry = new geometries::Line(p1, p2, name);

  viewPort->addGeometry(geometry);
  ui->listWidget->addItem(QString(geometry->getName().c_str()));
 
  haveGeometry();
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
  
  haveGeometry();
}


void MainWindow::addPolygonButton_clicked()
{
  if (!ui->polygonEditX->text().isEmpty())
    addPointOnPolygonButton_clicked();

  auto name = ui->polygonName->text().toStdString();
  geometries::Geometry * geometry;

  if (name.empty())
    geometry = new geometries::Polygon(pointsToPolygon);
  else
    geometry = new geometries::Polygon(pointsToPolygon, name);

  assert(pointsToPolygon.size() > 1);
  viewPort->addGeometry(geometry);
  ui->listWidget->addItem(QString(geometry->getName().c_str()));
  pointsToPolygon.clear();
 
  ui->tabWidget_2->setEnabled(true);
}

void MainWindow::connectButtons()
{
  /* connect buttons to insert geometry */
  connect(ui->addPointButton, &QPushButton::clicked,
    this, &MainWindow::addPointButton_clicked);
  connect(ui->addLineButton, &QPushButton::clicked,
    this, &MainWindow::addLineButton_clicked);
  connect(ui->addPointOnPolygonButton, &QPushButton::clicked,
    this, &MainWindow::addPointOnPolygonButton_clicked);
  connect(ui->addPolygonButton, &QPushButton::clicked,
    this, &MainWindow::addPolygonButton_clicked);

  /* connect zoom buttons */
  connect(ui->zoomInButton, &QPushButton::clicked,
    this, &MainWindow::zoomInButton_clicked);
  connect(ui->zoomOutButton, &QPushButton::clicked,
    this, &MainWindow::zoomOutButton_clicked);

  /* connect move window buttons */
  connect(ui->upButton, &QPushButton::clicked,
    this, &MainWindow::upButton_clicked);
  connect(ui->downButton, &QPushButton::clicked,
    this, &MainWindow::downButton_clicked);
  connect(ui->leftButton, &QPushButton::clicked,
    this, &MainWindow::leftButton_clicked);
  connect(ui->rightButton, &QPushButton::clicked,
    this, &MainWindow::rightButton_clicked);

  /* connect rotate buttons */
  connect(ui->leftRotateButton, &QPushButton::clicked,
    this, &MainWindow::leftRotateButton_clicked);
  connect(ui->rightRotateButton, &QPushButton::clicked,
    this, &MainWindow::rightRotateButton_clicked);
}

void MainWindow::hasNotGeometry()
{
  ui->tabWidget_2->setEnabled(false);
  ui->listWidget->setEnabled(false);
}

void MainWindow::haveGeometry()
{
  ui->tabWidget_2->setEnabled(true);
  ui->listWidget->setEnabled(true);
  ui->rb_origin->setChecked(true);
}
