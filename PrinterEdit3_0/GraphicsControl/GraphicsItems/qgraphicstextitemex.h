#ifndef UTEXTITEM_H
#define UTEXTITEM_H

#include <QGraphicsTextItem>

class QGraphicsTextItemEx: public QGraphicsTextItem
{
public:
    QGraphicsTextItemEx(QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool isHide;
    // QGraphicsItem interface
protected:
    void focusOutEvent(QFocusEvent *event);
};

#endif // UTEXTITEM_H
