#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H
#include "graphicsitembase.h"
#include "graphicsrectitem.h"
#include <QGraphicsItem>
#include "qgraphicstextitemex.h"
#include <QGraphicsProxyWidget>
#include <QTextEdit>
class GraphicsTextItem: public GraphicsRectItem
{
public:
    void setText(QString text);
    GraphicsTextItem(const QRect & rect ,QString text,QGraphicsItem * parent);

    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
    virtual QRectF  rect() ;
    virtual void multipleChoiceEvent();
    void enableStretch() { m_isStretch=true;}
    void unableStretch() { m_isStretch=false;}
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void uncheckedEvent();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    QGraphicsProxyWidget *m_Textwidget;
    QGraphicsTextItemEx *m_text;
    bool m_isStretch=true;//是否开启拉伸
};

#endif // GRAPHICSTEXTITEM_H
