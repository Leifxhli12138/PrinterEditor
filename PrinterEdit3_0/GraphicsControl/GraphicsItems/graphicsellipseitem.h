#ifndef GRAPHICSELLIPSEITEM_H
#define GRAPHICSELLIPSEITEM_H

#include <qgraphicsitem.h>
#include <QGraphicsSceneMouseEvent>
#include "graphicsrectitem.h"
#include "GraphicsControl\sizehandle.h"

class GraphicsEllipseItem : public GraphicsRectItem
{
public:
    GraphicsEllipseItem(const QRect & rect ,QGraphicsItem * parent);
    QPainterPath shape() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // GRAPHICSELLIPSEITEM_H
