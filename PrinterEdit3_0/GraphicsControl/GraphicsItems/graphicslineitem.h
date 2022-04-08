#ifndef GRAPHICSLINEITEM_H
#define GRAPHICSLINEITEM_H

#include <qgraphicsitem.h>
#include <QGraphicsSceneMouseEvent>
#include "graphicsrectitem.h"
#include "GraphicsControl\sizehandle.h"

class GraphicsLineItem: public GraphicsItemBase
{
public:
    GraphicsLineItem(const QPointF &startPoint ,const QPointF &endPoint,QGraphicsItem * parent);

        QRectF boundingRect() const;
        QPainterPath shape() const;
        virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
         virtual QRectF  rect() const
        {
            QRectF bounding (m_startPoint.x(), m_startPoint.y(),m_endPoint.x()-m_startPoint.x(),m_endPoint.y()-m_startPoint.y());
            return bounding;
        }
private:
    QPointF m_startPoint;
    QPointF m_endPoint;
protected:
    void updateGeometry();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // GRAPHICSLINEITEM_H
