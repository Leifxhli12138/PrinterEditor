#include "graphicsrectitem.h"
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QCursor>
#include <QDebug>
#include <QGraphicsEffect>
#include <QMenu>
#include <qmath.h>
#include <QGraphicsView>
#include "graphicsitembase.h"

GraphicsRectItem::GraphicsRectItem(const QRect & rect ,QGraphicsItem *parent)
    :GraphicsItemBase(parent)
    ,m_width(rect.width())
    ,m_height(rect.height())
{
    // handles创建锚点队列
    m_handles.reserve(SizeHandleRect::None);
    //枚举队列
    for (int i = SizeHandleRect::LeftTop; i <= SizeHandleRect::Rotate; ++i) {
        SizeHandleRect *shr = new SizeHandleRect(this, static_cast<SizeHandleRect::Direction>(i));
        m_handles.push_back(shr);
    }
    updateGeometry();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    m_delta =rect;
    this->setAcceptHoverEvents(true);
}

QRectF GraphicsRectItem::boundingRect() const
{
    QRectF bounding ( QPointF(m_delta.left(), m_delta.top()),QPointF(m_delta.right(),m_delta.bottom()));
    return bounding;
}

//用来控制检测碰撞collide和鼠标点击hit响应区域,返回图形轮廓
QPainterPath GraphicsRectItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return qt_graphicsItem_shapeFromPath(path,pen());
}

void GraphicsRectItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{
    GraphicsItemBase::resizeTo(dir,point);
    QPointF local = mapFromScene(point);
    QString dirName;
    m_delta= this->rect().toRect();
    switch (dir) {

    case SizeHandleRect::Right:
        m_delta.setRight(local.x());
        break;
    case SizeHandleRect::RightTop:
        dirName = "RightTop";
        m_delta.setTopRight(local.toPoint());
        break;
    case SizeHandleRect::RightBottom:
        dirName = "RightBottom";
        m_delta.setBottomRight(local.toPoint());
        break;
    case SizeHandleRect::LeftBottom:
        dirName = "LeftBottom";
        m_delta.setBottomLeft(local.toPoint());
        break;
    case SizeHandleRect::Bottom:
        dirName = "Bottom";
        m_delta.setBottom(local.y());
        break;
    case SizeHandleRect::LeftTop:
        dirName = "LeftTop";
        m_delta.setTopLeft(local.toPoint());
        break;
    case SizeHandleRect::Left:
        dirName = "Left";
        m_delta.setLeft(local.x());
        break;
    case SizeHandleRect::Top:
        dirName = "Top";
        m_delta.setTop(local.y());
        break;
    case SizeHandleRect::Rotate:
        dirName = "Rotate";
        setRotateEnd(point);
        break;
    default:
        break;
    }

    prepareGeometryChange();

    m_width = m_delta.width();
    m_height = m_delta.height();

    updateGeometry();

}

void GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //画矩形的实现
    QColor c = QColor(Qt::red);
    //    c.setAlpha(160);
    QLinearGradient result(rect().topLeft(), rect().topRight());
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
    painter->setPen(pen());
    painter->setBrush(result);
    painter->drawRect(rect());
}

