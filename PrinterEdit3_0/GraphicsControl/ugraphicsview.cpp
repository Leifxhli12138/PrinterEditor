#include "ugraphicsview.h"
#include <QDebug>
#include <QPen>

#define cout qDebug() << "[" <<__FILE__ <<":" <<__LINE__ << "]"


UGraphicsView::UGraphicsView(QWidget *parent) : QGraphicsView (parent)
{
    m_d_zoomDelta=0.1;  // 缩放的增量
    m_d_scaleValue=1.0;

    setRenderHint(QPainter::Antialiasing);//抗锯齿
    //设置背景透明
    //    this->setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: transparent;border:0px");

}
void UGraphicsView::ZoomIn()
{
    zoom(1 + m_d_zoomDelta);
}

// 缩小
void UGraphicsView::ZoomOut()
{
    zoom(1 - m_d_zoomDelta);
}
void UGraphicsView::zoom(qreal scaleFactor)
{
    // 防止过小或过大
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < UGraphicsView::MIN_SCALE || factor > UGraphicsView::MAX_SCALE)
        return;

    scale(scaleFactor, scaleFactor);
    m_d_scaleValue *= scaleFactor;
}

void UGraphicsView::wheelEvent(QWheelEvent *event){
    if(QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        // 滚轮的滚动量
        QPoint scrollAmount = event->angleDelta();
        // 正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
        scrollAmount.y() > 0 ? ZoomIn() :ZoomOut();
    }
    else{
        QGraphicsView::wheelEvent(event);
    }
}

QSizeF UGraphicsView::getSize(){
    return  QSizeF(this->scene()->width()*m_d_scaleValue,this->scene()->height()*m_d_scaleValue);
}

