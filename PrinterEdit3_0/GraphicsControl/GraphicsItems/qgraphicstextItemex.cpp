#include "qgraphicstextitemex.h"
#include <QStyleOptionGraphicsItem>

QGraphicsTextItemEx::QGraphicsTextItemEx(QGraphicsItem *parent):QGraphicsTextItem (parent)
  ,isHide(true)
{

}

void QGraphicsTextItemEx::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    if(!isHide){
        QStyleOptionGraphicsItem op;
        op.initFrom(widget);
        op.state = QStyle::State_None;
        QGraphicsTextItem::paint(painter,&op,widget);
    }
}

void QGraphicsTextItemEx::focusOutEvent(QFocusEvent *event){
    isHide=true;
    setTextInteractionFlags(Qt::NoTextInteraction); //取消编辑状态
}
