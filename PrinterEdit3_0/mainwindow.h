#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "GraphicsControl/ugraphicsscene.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addShape() ;
    void updateUI();

private:
    Ui::MainWindow *ui;
    QActionGroup * group;
    QTimer      m_timer;
    QString path;
};

#endif // MAINWINDOW_H
