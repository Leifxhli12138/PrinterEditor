#ifndef GRAPHICSITEMBASE_H
#define GRAPHICSITEMBASE_H

#include <qgraphicsitem.h>
#include <QGraphicsSceneMouseEvent>
#include "GraphicsControl\sizehandle.h"
#include "GraphicsControl\Enums.h"

class GraphicsItemBase : public QAbstractGraphicsShapeItem
{
public:
    GraphicsItemBase(QGraphicsItem * parent );
    void setRotateStart(QPointF point );
    void setRotateEnd(QPointF point);
    enum {Type = UserType+1};
    int  type() const { return Type; }
    SizeHandleRect::Direction hitTest(const QPointF & point ) const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
    virtual QPointF origin () const { return QPointF(0,0); }
    virtual Qt::CursorShape getCursor(SizeHandleRect::Direction dir, QPointF point );
    virtual QRectF  rect() const { return QRectF(0,0,0,0);}
    virtual void multipleChoiceEvent(){}
protected:
    virtual void uncheckedEvent(){}
    virtual void selectedEvent(){}
    virtual void updateGeometry();
    void setRect(QRectF rect);
    void setState(SelectionHandleState st);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    typedef QVector<SizeHandleRect*> Handles;
    Handles m_handles;
    qreal m_angle=0;
    qreal m_fLastAngle=0;
    QPointF m_mouseRotateStart;
    QPainterPath qt_graphicsItem_shapeFromPath(const QPainterPath &path, const QPen &pen) const;
};

#endif // GRAPHICSITEMBASE_H
