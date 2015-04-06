#include "mainwindow.h"
#include "line.h"
#include "point.h"
#include "ui_mainwindow.h"
#include "viewPort.h"
#include "window.h"

#include <QIcon>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  Q_INIT_RESOURCE(images);

  ui->setupUi(this);
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
    showCriticalMessage("Preencha os campos corretamente!");
    return;
  }

  geometries::Point p1(ptoX1.toFloat(), ptoY1.toFloat());
  geometries::Point p2(ptoX2.toFloat(), ptoY2.toFloat());

  viewPort_->addGeometry(new geometries::Line(p1, p2));
}
