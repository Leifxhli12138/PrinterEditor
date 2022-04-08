#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H
#include "graphicsitembase.h"
#include "graphicsrectitem.h"
#include <QGraphicsItem>
#include "qgraphicstextitemex.h"

class GraphicsTextItem: public GraphicsRectItem
{
public:
    void setText(QString text);
    GraphicsTextItem(const QRect & rect ,QString text,QGraphicsItem * parent);

    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
    virtual QRectF  rect() ;
    void enableStretch() { m_isStretch=true;}
    void unableStretch() { m_isStretch=false;}
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void uncheckedEvent();
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QGraphicsTextItemEx * m_textItem;
    bool m_isStretch=true;//是否开启拉伸
    // QGraphicsItem interface

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSTEXTITEM_H
