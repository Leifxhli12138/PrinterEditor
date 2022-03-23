#include "graphicsellipseitem.h"
#include <QPainter>
#include <QDebug>
#include <QRadialGradient>
#include "graphicsitembase.h"


GraphicsEllipseItem::GraphicsEllipseItem(const QRect &rect, QGraphicsItem *parent)
    :GraphicsRectItem(rect,parent)
{
}

QPainterPath GraphicsEllipseItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return qt_graphicsItem_shapeFromPath(path,pen());
}

void GraphicsEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //画圆形的实现
    QColor c = QColor(Qt::red);
    c.setAlpha(160);
    QRectF rc = rect();
    qreal radius = qMax(rc.width(),rc.height());
    QRadialGradient result(rc.center(),radius);
    result.setColorAt(0, c.light(200));
    result.setColorAt(0.5, c.dark(150));
    result.setColorAt(1, c);
    painter->setPen(pen());
    painter->setBrush(result);
    painter->drawEllipse(rc);
//    painter->setPen(QPen(Qt::red,3,Qt::SolidLine));
//    painter->drawLine(QPointF(0,0),QPointF(rc.width(),rc.height()));
    painter->end();
}
