#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
 //   QPoint lastPos;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    //QMouseEvent* mousePressEvent();
   // QMouseEvent* mouseMoveEvent(QPoint lastPos);

};

#endif // MAINWINDOW_H
