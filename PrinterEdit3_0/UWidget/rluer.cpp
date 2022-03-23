#include "rluer.h"
#include "ui_rluer.h"
#include "GraphicsControl/ugraphicsscene.h"
#include <QRegion>
#include <QMargins>
#include <QPixmap>

Rluer::Rluer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rluer)
{
    ui->setupUi(this);
    installEventFilter(this);
    setMouseTracking(true);
    //重新设置弹簧的大小
    ui->topMargin->changeSize(20,m_rluerHeight);
    ui->leftMargin->changeSize(m_rluerHeight,20);
    this->layout()->invalidate();


    m_scene = new UGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    connect(m_scene,&UGraphicsScene::initSizeOverEvent, this,&Rluer::updateOffset);
    connect(m_scene,&UGraphicsScene::rluerDispalyItemPoint, [&](){this->update();});
    m_scene->createArea(QRectF(0 , 0 , 100, 100));
    connect(ui->graphicsView->horizontalScrollBar(),&QScrollBar::valueChanged,this,&Rluer::updateOffset);
    connect(ui->graphicsView->verticalScrollBar(),&QScrollBar::valueChanged,this,&Rluer::updateOffset);

}

Rluer::~Rluer()
{
    delete ui;
}

void Rluer::showEvent(QShowEvent*){
    updateOffset();
}

void Rluer::resizeEvent(QResizeEvent*){
    updateOffset();
}

//更新scene的相对位置，单位mm
void Rluer::updateOffset(){
    setOffsetX(ui->graphicsView->pixelToMM(ui->graphicsView->mapToScene(0,0).x()));
    setOffsetY(ui->graphicsView->pixelToMM(ui->graphicsView->mapToScene(0,0).y()));
}

UGraphicsView* Rluer::getView(){
    return ui->graphicsView;
}

void Rluer::wheelEvent(QWheelEvent *event)
{
    if(QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        //获取scene相对于view的坐标
        updateOffset();
    }
    else{
        QWidget::wheelEvent(event);
    }

}
void Rluer::paintEvent(QPaintEvent *event){

    QPainter* painter=new QPainter(this);
    drawRluer(painter);
    QWidget::paintEvent(event);
}

void Rluer::drawRluer(QPainter* painter){
    qreal _scaleValue=ui->graphicsView->scaleValue();
    qreal actualWidth=width();
    qreal actualHeight=height();
    qreal oneMMPixel=ui->graphicsView->getOneMMPixel();
    qreal mm=oneMMPixel * _scaleValue;//1毫米所占像素
    painter->fillRect(rect(),Qt::gray);
    painter->setRenderHint(QPainter::Qt4CompatiblePainting);//抗锯齿
    painter->fillRect(QRectF(0,0,actualWidth,m_rluerHeight),QBrush(Qt::GlobalColor::white));
    painter->fillRect(QRectF(0,m_rluerHeight,m_rluerHeight,actualHeight),QBrush(Qt::GlobalColor::white));
    qreal rluerHeight=m_rluerHeight-1;
    painter->drawLine(QPointF(rluerHeight,rluerHeight),QPointF(rluerHeight,actualHeight));
    painter->drawLine(QPointF(rluerHeight,rluerHeight),QPointF(actualWidth,rluerHeight));
    //设置绘图有效区域
    QRegion region1(QRect(m_rluerHeight, 0, actualWidth, m_rluerHeight));
    QRegion region2(QRect(0,m_rluerHeight,m_rluerHeight,actualHeight));
    painter->setClipRegion(region1+region2);

    cm=_scaleValue<0.3?50:10;//缩放比例小于0.3时，改为50cm画一次10cm分界线

    qreal marginTop=ui->graphicsView->pixelToMM(m_scene->getMargin()->top());
    qreal newOffsetY=offsetY-marginTop;
    int j=qRound(newOffsetY);
    qreal difference =(newOffsetY-j)*mm;//坐标尺是整数，所以要计算小数（毫米)所占的像素数
    for(qreal i=m_rluerHeight-difference;i<actualHeight;i+=mm,++j){
        if(j%cm==0)
        {
            if(j<=0)
                painter->setPen(Qt::GlobalColor::red);
            else
                painter->setPen(Qt::GlobalColor::black);
            painter->drawText(QPointF(0,i+12),QString::number(j));
            painter->setPen(Qt::GlobalColor::black);
            painter->drawLine(QPointF(0,i),QPointF( m_rluerHeight,i));
        }
        else if(j%cmHalf==0)
        {
            painter->drawLine(QPointF(m_rluerHeight-RluerHeightHalf,i),QPointF( m_rluerHeight,i));
        }
        else
        {
            if(_scaleValue>0.5)
                painter->drawLine(QPointF(m_rluerHeight-RluerHeightHalfHalf,i),QPointF( m_rluerHeight,i));
        }
    }

    qreal marginLeft=ui->graphicsView->pixelToMM(m_scene->getMargin()->left());
    qreal newOffsetX=offsetX-marginLeft;//减去边距所占毫米数
    j=qRound(newOffsetX);
    difference=(newOffsetX-j)*mm;//坐标尺是整数，所以要计算小数所占的像素数
    for(double i=m_rluerHeight-difference;i<actualWidth;i+=mm,++j){
        if(j%cm==0)
        {
            if(j<=0)
                painter->setPen(Qt::GlobalColor::red);
            else
                painter->setPen(Qt::GlobalColor::black);
            painter->drawText(QPointF(i,15),QString::number(j));
            painter->setPen(Qt::GlobalColor::black);
            painter->drawLine(QPointF(i,0),QPointF(i, m_rluerHeight));
        }
        else if(j%cmHalf==0)
        {
            painter->drawLine(QPointF(i,m_rluerHeight-RluerHeightHalf),QPointF(i,m_rluerHeight));
        }
        else
        {
            if(_scaleValue>0.5)
                painter->drawLine(QPointF(i,m_rluerHeight-RluerHeightHalfHalf),QPointF(i, m_rluerHeight));
        }
    }

    //选中item时发生
    drawSelectedElement(painter);
    painter->end();

}
void Rluer::drawSelectedElement(QPainter* painter){
    QList<QGraphicsItem*> items= m_scene->selectedItems();
    if(items.count()==0){
        return;
    }
    if(items.count()==1){

        qreal _scaleValue=ui->graphicsView->scaleValue();
        QPointF b=ui->graphicsView->mapToScene(0,0);
        //计算item在视场中的位置
        qreal x1= m_rluerHeight+(items.first()->x()-b.x())*_scaleValue;
        qreal y1= m_rluerHeight+(items.first()->y()-b.y())*_scaleValue;
        qreal x2= x1+(items.first()->boundingRect().width()*_scaleValue);
        qreal y2= y1+(items.first()->boundingRect().height()*_scaleValue);

        painter->setPen(QPen(QColor(0,150,0),1,Qt::SolidLine));
        painter->drawLine(QPointF(x1,0),QPointF(x1, m_rluerHeight));
        painter->drawLine(QPointF(x2,0),QPointF(x2, m_rluerHeight));
        painter->drawLine(QPointF(0,y1),QPointF(m_rluerHeight, y1));
        painter->drawLine(QPointF(0,y2),QPointF(m_rluerHeight, y2));
    }
}
