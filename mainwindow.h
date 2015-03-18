#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editor.h"

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionExit_triggered();

  void on_actionNew_triggered();

  void on_actionWires_triggered(bool checked);

  void on_actionRotate_right_triggered();

  void on_actionRotate_left_triggered();

  private:
  Ui::MainWindow *ui;
  Editor * editor;
  QGraphicsScene * scene;
};

#endif // MAINWINDOW_H
