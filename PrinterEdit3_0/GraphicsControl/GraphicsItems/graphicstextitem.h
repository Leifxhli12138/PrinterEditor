#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H
#include "graphicsitembase.h"
#include <QGraphicsTextItem>

class GraphicsTextItem: public GraphicsItemBase
{
public:
    GraphicsTextItem(const QString &text, QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // GRAPHICSTEXTITEM_H
