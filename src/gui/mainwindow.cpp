#include "bezier.h"
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
  const int RATE_TO_MOVE = 5;
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  Q_INIT_RESOURCE(images);

  ui->setupUi(this);
  connectButtons();
  
  window.reset(new Window(geometries::Point(-100.0, -100.0), geometries::Point(100.0, 100.0)));
  viewPort.reset(new ViewPort(window.get(), ui->groupBox));
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
  std::unique_ptr<geometries::Point> point(new geometries::Point(x.toFloat(), y.toFloat()));

  ui->pointEditX->setText("");
  ui->pointEditY->setText("");

  if (name.empty())
    geometry = new geometries::Polygon(std::vector<geometries::Point*>{point.release()});
  else {
    geometry = new geometries::Polygon(std::vector<geometries::Point*>{point.release()}, name);
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
  std::unique_ptr<geometries::Point> p1(new geometries::Point(ptoX1.toFloat(), ptoY1.toFloat()));
  std::unique_ptr<geometries::Point> p2(new geometries::Point(ptoX2.toFloat(), ptoY2.toFloat()));
  
  ui->lineX1->setText("");
  ui->lineY1->setText("");
  ui->lineX2->setText("");
  ui->lineY2->setText("");

  geometries::Geometry *geometry;

  if (name.empty())
    geometry = new geometries::Line(std::vector<geometries::Point*>{ p1.release(), p2.release() });
  else
    geometry = new geometries::Line(p1.release(), p2.release(), name);

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

  pointsToPolygon.push_back(new geometries::Point(x.toFloat(), y.toFloat()));
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

void MainWindow::addCurveButton_clicked()
{
  auto x0 = ui->x0Bezier->text();
  auto y0 = ui->y0Bezier->text();
  auto x1 = ui->x1Bezier->text();
  auto y1 = ui->y1Bezier->text();
  auto x2 = ui->x2Bezier->text();
  auto y2 = ui->y2Bezier->text();
  auto x3 = ui->x3Bezier->text();
  auto y3 = ui->y3Bezier->text();

  if (x0.isEmpty() || y0.isEmpty() ||
      x1.isEmpty() || y1.isEmpty() ||
      x2.isEmpty() || y2.isEmpty())
  {
    showCriticalMessage("Add the X and Y coordinates,\nto add the point to Polygon!");
    return;
  }

  std::vector<geometries::Point*> pointsToBezier = { 
    new geometries::Point(x0.toFloat(), y0.toFloat()),
    new geometries::Point(x1.toFloat(), y1.toFloat()),
    new geometries::Point(x2.toFloat(), y2.toFloat())};

  if (!(x3.isEmpty() && y3.isEmpty()))
    pointsToBezier.push_back(new geometries::Point(x3.toFloat(), y3.toFloat()));
    
  ui->x0Bezier->setText("");
  ui->y0Bezier->setText("");
  ui->x1Bezier->setText("");
  ui->y1Bezier->setText("");
  ui->x2Bezier->setText("");
  ui->y2Bezier->setText("");
  ui->x3Bezier->setText("");
  ui->y3Bezier->setText("");
  
  auto name = ui->polygonName->text().toStdString();
  geometries::Geometry * geometry;

  if (name.empty())
    geometry = new geometries::Bezier(pointsToBezier);
  else
    geometry = new geometries::Bezier(pointsToBezier, name);

  viewPort->addGeometry(geometry);
  ui->listWidget->addItem(QString(geometry->getName().c_str()));
  pointsToBezier.clear();

  haveGeometry();
  ui->tabWidget_2->setEnabled(true);
}

void MainWindow::applyTranslate_clicked()
{
  auto dx = ui->dxTranslate->text();
  auto dy = ui->dyTranslate->text();

  auto currentItem = ui->listWidget->currentItem();
  if (!currentItem)
    return;

  if (dx.isEmpty() ||
      dy.isEmpty())
  {
    showCriticalMessage("Add the DX and DY coordinates,\nto to translate Geometry!");
    return;
  }

  auto geometryName = currentItem->text().toStdString();
  window->translateGeometry(geometryName, dx.toFloat(), dy.toFloat(), 0);
  ui->dxTranslate->setText("0");
  ui->dyTranslate->setText("0");
  viewPort->redraw();
}

void MainWindow::applyScaling_clicked()
{
  auto sx = ui->sxScaling->text();
  auto sy = ui->syScaling->text();

  auto currentItem = ui->listWidget->currentItem();
  if (!currentItem)
    return;

  if (sx.isEmpty() ||
      sy.isEmpty())
  {
    showCriticalMessage("Add the SX and SY coordinates,\nto to scaling Geometry!");
    return;
  }

  auto geometryName = currentItem->text().toStdString();
  window->scalingGeometry(geometryName, sx.toFloat(), sy.toFloat(), 0);
  ui->sxScaling->setText("1");
  ui->syScaling->setText("1");
  viewPort->redraw();

}

void MainWindow::rotate(float angle)
{
  if (ui->rb_world->isChecked())
  {
    window->rotateWindow(angle);
  }
  else
  {
    auto currentItem = ui->listWidget->currentItem();
    if (!currentItem)
      return;

    auto geometryName = currentItem->text().toStdString();

    if (ui->rb_origin->isChecked())
    {
      window->rotateOrigin(geometryName, angle);
    }
    else
    {
      float rotateX = ui->rotatePointX->text().toFloat();
      float rotateY = ui->rotatePointY->text().toFloat();
      window->rotatePoint(geometryName, geometries::Point(rotateX, rotateY), angle);
    }
  }
  viewPort->redraw();
}

void MainWindow::leftRotateButton_clicked()
{
  float angle = 360.f - ui->angleSpinBox->text().toFloat();
  rotate(angle);
}

void MainWindow::rightRotateButton_clicked()
{
  float angle = ui->angleSpinBox->text().toFloat();  
  rotate(angle);
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
  connect(ui->addCurveButton, &QPushButton::clicked,
    this, &MainWindow::addCurveButton_clicked);

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

  /* connect transforms buttons */
  connect(ui->applyTranslate, &QPushButton::clicked,
    this, &MainWindow::applyTranslate_clicked);
  connect(ui->applyScaling, &QPushButton::clicked,
    this, &MainWindow::applyScaling_clicked);
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
