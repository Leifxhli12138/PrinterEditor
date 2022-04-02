#include "graphicstextitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QAbstractTextDocumentLayout>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>
#include <QImage>

GraphicsTextItem:: GraphicsTextItem(const QRect & rect ,QString text,QGraphicsItem * parent)
    :GraphicsRectItem(rect,parent)
{
    m_textItem = new QGraphicsTextItemEx(this);
    m_textItem->setPlainText(text);
    QFont fnt = QFont("Courier", 15, QFont::Normal);
    fnt.setStretch(QFont::SemiExpanded);
    m_textItem->setFont(fnt);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QRectF  GraphicsTextItem::rect(){
    qreal x,y,w,h;
    x=boundingRect().x();
    y=boundingRect().y();
    w=boundingRect().width();
    h=boundingRect().height();
    return QRectF(x,y,w,h);
}

//QVariant GraphicsTextItem::itemChange(GraphicsItemChange change, const QVariant &value){
//   // GraphicsItemBase::itemChange(change,value);
//}

void GraphicsTextItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point){
    GraphicsRectItem::resizeTo(dir, point);
}
void GraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(m_textItem!=nullptr&&m_textItem->isHide){
        if(m_isStretch){//启用拉伸状态时
            painter->save();
            QFontMetrics metrics(painter->font());
            qreal fontWidth=metrics.width(m_textItem->toPlainText());
            qreal xScale=rect().width()/fontWidth;
            qreal yScale=rect().height()/metrics.height();
            painter->scale(xScale,yScale);
            QPointF postion=QPointF(rect().x()/xScale,rect().y()/yScale+metrics.ascent());
            painter->drawText(postion, m_textItem->toPlainText());
        }
        else{//关闭拉伸状态时
            int minWidth= 0.75 * qMin(qAbs(rect().width()), qAbs(rect().height()));
            if(minWidth<=0)
                return;
            QFont font=painter->font();
            font.setPixelSize(minWidth);
            painter->save();
            painter->setFont(font);
            if(boundingRect().width()<0&& boundingRect().height()<0){
                painter->scale( -1, -1 );
                painter->drawText(-rect().x(),-rect().y(),-rect().width(),-rect().height(), Qt::AlignVCenter|Qt::AlignLeft, m_textItem->toPlainText());
            }
            else if(boundingRect().width()<0){
                painter->scale( -1, 1 );
                painter->drawText(-rect().x(),rect().y(),-rect().width(),rect().height(), Qt::AlignVCenter|Qt::AlignLeft, m_textItem->toPlainText());
            }
            else if(boundingRect().height()<0){
                painter->scale( 1, -1 );
                painter->drawText(rect().x(),-rect().y(),rect().width(),-rect().height(), Qt::AlignVCenter|Qt::AlignLeft, m_textItem->toPlainText());
            }
            else{
                painter->drawText(rect(), Qt::AlignVCenter|Qt::AlignLeft, m_textItem->toPlainText());
            }
        }
        painter->restore();
    }
}

void GraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    m_textItem->isHide=false;
    m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->update();
}

