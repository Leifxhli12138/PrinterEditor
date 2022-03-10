#ifndef SIZEHANDLE
#define SIZEHANDLE

#include <QGraphicsRectItem>
#include <QList>
#include "Enums.h"

QT_BEGIN_NAMESPACE
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE


using namespace PrinterEdit3_0;

class SizeHandleRect :public QGraphicsRectItem
{
public:
    enum Direction { LeftTop , Top, RightTop, Right, RightBottom, Bottom, LeftBottom, Left ,Rotate, Center, None};

    SizeHandleRect(QGraphicsItem* parent , Direction d);

    Direction dir() const  { return m_dir; }
    void setState(SelectionHandleState st);
    bool hitTest( const QPointF & point );
    void setScale(qreal scale);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal m_scale;
    const Direction m_dir;
    QPoint m_startPos;
    QPoint m_curPos;
    QSize m_startSize;
    QSize m_curSize;
    QGraphicsItem *m_resizable;
    SelectionHandleState m_state;
};


#endif // SIZEHANDLE

