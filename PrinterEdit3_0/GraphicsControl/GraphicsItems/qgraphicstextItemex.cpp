#include "qgraphicstextitemex.h"
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QPainter>

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
//        QFontMetrics metrics(painter->font());
//        QStringList texts=this->toPlainText().split("\n");
//        //找出占位最长的一行
//        qreal maxfontWidth=0;
//        for(int i=0;i<texts.count();++i){
//            qreal len=metrics.width(texts[i]);
//            if(maxfontWidth<len){
//                maxfontWidth=len;
//            }
//        }
//       qDebug() << this->toPlainText();
    }
}

void QGraphicsTextItemEx::focusOutEvent(QFocusEvent *event){
    isHide=true;
    setTextInteractionFlags(Qt::NoTextInteraction); //取消编辑状态
}
