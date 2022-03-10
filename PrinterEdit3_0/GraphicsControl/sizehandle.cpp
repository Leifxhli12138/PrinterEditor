#include "sizehandle.h"
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <qdebug.h>

SizeHandleRect::SizeHandleRect(QGraphicsItem* parent , Direction d)
    :QGraphicsRectItem(0,0,SELECTION_HANDLE_SIZE,SELECTION_HANDLE_SIZE,parent)
    ,m_dir(d)
    ,m_resizable(parent)
    ,m_state(SelectionHandleOff)
{
    setParentItem(parent);
    hide();
}

void SizeHandleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //画锚点
    //  c.setAlpha(200);
    painter->setPen(QPen(Qt::red,1,Qt::SolidLine));

    if ( m_dir == Rotate )
    {
        painter->setBrush(QBrush(Qt::blue));
        painter->drawEllipse(rect());
    }
    else if(m_dir ==Top || m_dir ==Bottom){
        QPoint p1=QPoint( 0,rect().height()/2);
        QPoint p2=QPoint(rect().width()+p1.x(),p1.y());
        painter->setPen(QPen(Qt::red,1,Qt::DashLine));
        painter->drawLine(QLine(p1,p2));
    }
    else if(m_dir ==Left || m_dir ==Right){
        QPoint p1=QPoint( rect().width()/2,0);
        QPoint p2=QPoint( p1.x(),rect().height()-p1.y());
        painter->setPen(QPen(Qt::red,1,Qt::DashLine));
        painter->drawLine(QLine(p1,p2));
    }
    else{
        painter->setPen(QPen(Qt::red,1,Qt::SolidLine));
        painter->drawRect(rect());
    }
}

//设置拉伸手柄状态
void SizeHandleRect::setState(SelectionHandleState st)
{
    if (st == m_state)
        return;
    switch (st) {
    case SelectionHandleOff:
        hide();
        break;
    case SelectionHandleInactive:
    case SelectionHandleActive:
        show();
        break;
    }
    m_state = st;
}

//判断鼠标是否在句柄上
bool SizeHandleRect::hitTest(const QPointF &point)
{
    QPointF pt = mapFromScene(point);
    return rect().contains(pt);
}






