#include "graphicPoint.h"
#include "line.h"
#include "mainwindow.h"
#include "point.h"
#include "ui_mainwindow.h"
#include "viewPort.h"
#include "window.h"

#include <QIcon>
#include <QMessageBox>

#include <assert.h>
#include "polygon.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  Q_INIT_RESOURCE(images);

  ui->setupUi(this);
  connectButtons();
  window_ = std::make_unique<Window>(800, 600);
  viewPort_ = std::make_unique<ViewPort>(window_.get(), ui->groupBox);
  ui->verticalLayout_3->addWidget(viewPort_.get());
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_upButton_clicked()
{

}

void MainWindow::on_leftButton_clicked()
{

}

void MainWindow::on_downButton_clicked()
{

}

void MainWindow::on_rightButton_clicked()
{

}

void MainWindow::on_leftRotateButton_clicked()
{

}

void MainWindow::on_rightRotateButton_clicked()
{

}

void MainWindow::on_zoomInButton_clicked()
{

}

void MainWindow::on_zoomOutButton_clicked()
{

}


void MainWindow::addPointButton_clicked()
{
  auto x = ui->pointEditX->text();
  auto y = ui->pointEditY->text();

  if (ui->pointName->text().isEmpty() ||
      x.isEmpty() ||
      y.isEmpty())
  {
    showCriticalMessage("Fill in the fields correctly!");
    return;
  }

  viewPort_->addGeometry(new geometries::GraphicPoint(x.toFloat(), y.toFloat()));
}

void MainWindow::showCriticalMessage(std::string message)
{
  QMessageBox::critical(this,
                        tr("Critical"),
                        QString(message.c_str()),
                        QMessageBox::Ok);
}

void MainWindow::on_addLineButton_clicked()
{
  auto ptoX1 = ui->lineX1->text();
  auto ptoY1 = ui->lineY1->text();
  auto ptoX2 = ui->lineX2->text();
  auto ptoY2 = ui->lineY2->text();

  if (ui->LineName->text().isEmpty() ||
      ptoX1.isEmpty() ||
      ptoY1.isEmpty() ||
      ptoX2.isEmpty() ||
      ptoY2.isEmpty())
  {
    showCriticalMessage("Fill in the fields correctly!");
    return;
  }

  geometries::Point p1(ptoX1.toFloat(), ptoY1.toFloat());
  geometries::Point p2(ptoX2.toFloat(), ptoY2.toFloat());

  viewPort_->addGeometry(new geometries::Line(p1, p2));
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

  if (ui->polygonName->text().isEmpty())
  {
    showCriticalMessage("Set a name to Polygon");
    return;
  }
  assert(pointsToPolygon.size() > 1);
  viewPort_->addGeometry(new geometries::Polygon(pointsToPolygon));
  pointsToPolygon.clear();
}

void MainWindow::connectButtons()
{
  connect(ui->addPointButton, &QPushButton::clicked,
    this, &MainWindow::addPointButton_clicked);
  connect(ui->addLineButton, &QPushButton::clicked,
    this, &MainWindow::addPointButton_clicked);
  connect(ui->addPointOnPolygonButton, &QPushButton::clicked,
    this, &MainWindow::addPointOnPolygonButton_clicked);
  connect(ui->addPolygonButton, &QPushButton::clicked,
    this, &MainWindow::addPolygonButton_clicked);
}
