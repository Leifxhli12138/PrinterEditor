#include "graphicslineitem.h"
#include <QPainter>
#include <QDebug>
#include <QRadialGradient>
#include "graphicsitembase.h"


GraphicsLineItem::GraphicsLineItem(const QPointF &startPoint ,const QPointF &endPoint,QGraphicsItem * parent)
    :GraphicsItemBase(parent),
      m_startPoint(startPoint),
      m_endPoint(endPoint)
{
    // handles创建锚点队列
    m_handles.reserve(SizeHandleRect::None);
    //枚举队列
    SizeHandleRect *leftTop = new SizeHandleRect(this, static_cast<SizeHandleRect::Direction>(SizeHandleRect::LeftTop));
    m_handles.push_back(leftTop);
    SizeHandleRect *rightBottom = new SizeHandleRect(this, static_cast<SizeHandleRect::Direction>(SizeHandleRect::RightBottom));
    m_handles.push_back(rightBottom);
    updateGeometry();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);//接受悬停事件
}
QRectF GraphicsLineItem::boundingRect() const
{
    QRectF bounding (m_startPoint.x(), m_startPoint.y(),m_endPoint.x()-m_startPoint.x(),m_endPoint.y()-m_startPoint.y());
    return bounding;
}

QPainterPath GraphicsLineItem::shape() const
{
    QPainterPath path;
    path.lineTo(QPointF(m_endPoint));
    path.lineTo(QPointF(m_startPoint));
    return qt_graphicsItem_shapeFromPath(path,pen());
}

//设置句柄位置
void GraphicsLineItem::updateGeometry(){

    const QRectF &geom = this->boundingRect();
    const int wHalf = SELECTION_HANDLE_SIZE>>1;
    const int hHalf = SELECTION_HANDLE_SIZE>>1;

    const Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it) {
        SizeHandleRect *hndl = *it;;
        switch (hndl->dir()) {
        case SizeHandleRect::LeftTop:
            hndl->setPos(geom.x() - wHalf, geom.y()- hHalf );
            break;
        case SizeHandleRect::RightBottom:
            hndl->setPos(geom.x() + geom.width() - wHalf , geom.y()+ geom.height() - hHalf  );
            break;
        default:
            break;
        }
    }
}

void GraphicsLineItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{
    GraphicsItemBase::resizeTo(dir,point);
    QPointF local = mapFromScene(point);
    switch (dir) {
    case SizeHandleRect::RightBottom:
        m_endPoint=local.toPoint();
        break;
    case SizeHandleRect::LeftTop:
        m_startPoint=local.toPoint();
        break;
    default:
        break;
    }

    prepareGeometryChange();

    updateGeometry();

}

void GraphicsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //画线的实现
    painter->setPen(pen());
    painter->drawLine(m_startPoint,m_endPoint);
}
