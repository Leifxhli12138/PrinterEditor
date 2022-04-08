#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include <qgraphicsitem.h>
#include <QGraphicsSceneMouseEvent>
#include "GraphicsControl\sizehandle.h"
#include "graphicsitembase.h"

class GraphicsRectItem : public GraphicsItemBase
{
public:
    GraphicsRectItem(const QRect & rect,QGraphicsItem * parent);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
     virtual QRectF  rect() const
    {
        QRectF bounding ( m_delta.left(), m_delta.top(),m_width,m_height);
        return bounding;
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    qreal m_width;
    qreal m_height;
    QRect m_delta ;
};

#endif // GRAPHICSRECTITEM_H
