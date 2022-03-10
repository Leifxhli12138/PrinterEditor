#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GraphicsControl/ugraphicsscene.h"
#include <QFileDialog>
#include <QPainter>
#include <QGraphicsView>
#include "GraphicsControl/GraphicsItems/graphicsitembase.h"
#include <QSvgGenerator>
#include "UWidget/rluer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    group = new QActionGroup(this);
    group->addAction(ui->actionSelection);
    group->addAction(ui->actionEllipse);
    group->addAction(ui->actionRectangle);
    group->addAction(ui->actionText);
    group->addAction(ui->actionLine);
    ui->actionSelection->setChecked(true);

    resize(800,600);

    connect(ui->actionSelection,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(ui->actionEllipse,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(ui->actionRectangle,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(ui->actionText,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(ui->actionLine,SIGNAL(triggered()),this,SLOT(addShape()));

    connect(&m_timer,SIGNAL(timeout()),this,SLOT(updateUI()));
    m_timer.start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addShape()
{
    if ( sender() == ui->actionEllipse )
        UGraphicsScene::c_drawShape =ItemShape::ellipse;
    if ( sender() == ui->actionRectangle )
        UGraphicsScene::c_drawShape = ItemShape::rectangle;
    if ( sender() == ui->actionSelection )
        UGraphicsScene::c_drawShape = ItemShape::selection;
    if ( sender() == ui->actionLine )
        UGraphicsScene::c_drawShape = ItemShape::line;
    if ( sender() == ui->actionText)
        UGraphicsScene::c_drawShape = ItemShape::text;
}

void MainWindow::updateUI()
{
    if ( UGraphicsScene::c_drawShape == ItemShape::ellipse )
        ui->actionEllipse->setChecked(true);
    else if ( UGraphicsScene::c_drawShape == ItemShape::rectangle )
        ui->actionRectangle->setChecked(true);
    else if (UGraphicsScene::c_drawShape == ItemShape::selection )
        ui->actionSelection->setChecked(true);
    else if (UGraphicsScene::c_drawShape == ItemShape::text )
        ui->actionText->setChecked(true);
    else if (UGraphicsScene::c_drawShape == ItemShape::line )
        ui->actionLine->setChecked(true);

}

