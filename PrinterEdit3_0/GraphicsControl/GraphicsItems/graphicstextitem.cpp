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
    //    QTextBlockFormat format;
    //    format.setAlignment(Qt::AlignCenter);
    //    QTextCursor cursor = m_textItem->textCursor();
    //    cursor.select(QTextCursor::Document);
    //    cursor.mergeBlockFormat(format);
    //    cursor.clearSelection();
    //    m_textItem->setTextCursor(cursor);

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

void GraphicsTextItem::uncheckedEvent(){

    m_textItem->isHide=true;
    m_textItem->setTextInteractionFlags(Qt::NoTextInteraction); //取消编辑状态
}
void GraphicsTextItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point){
    GraphicsRectItem::resizeTo(dir, point);
    if(! m_textItem->isHide)
        this->uncheckedEvent();
}
//textbox限制大小，以及滚动条没有实现
void GraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(m_textItem!=nullptr&&m_textItem->isHide){
        qreal textItemX=rect().x();
        qreal textItemY=rect().y();
        if(rect().width()<0)
            textItemX+=rect().width();
        if(rect().height()<0)
            textItemY+=rect().height();
        if(!rect().height()||!rect().width())return;
        //设置textBox新坐标
        m_textItem->setPos(QPointF(textItemX,textItemY));
        //多行文本绘制
        QFontMetrics metrics(painter->font());
        QStringList texts=m_textItem->toPlainText().split("\n");

        if(&texts ==nullptr ||texts.count()==0)return;
        if(m_isStretch){//启用拉伸状态时
            painter->save();
            //找出占位最长的一行
            int maxItem=0;
            qreal maxfontWidth=0;
            for(int i=0;i<texts.count();++i){
                qreal len=metrics.width(texts[i]);
                if(maxfontWidth<len){
                    maxfontWidth=len;
                    maxItem=i;
                }
            }
            if(maxfontWidth==0)return;
            qreal xScale=rect().width()/maxfontWidth;
            qreal yScale=rect().height()/metrics.height()/texts.count();
            painter->scale(xScale,yScale);

            qreal x=rect().x()/xScale;
            qreal y=(rect().y()/yScale)-metrics.descent();
            qreal fontHeight=metrics.height();
            for(int i=0;i<texts.count();++i){
                QPointF postion=QPointF(x,fontHeight*(i+1)+y);
                painter->drawText(postion, texts[i]);
            }
        }
        else{//关闭拉伸状态时
            QFontInfo fInfo(painter->font());
            qreal  minWidth=  qAbs(rect().height())/ (metrics.height()+metrics.descent())/texts.count()*fInfo.pixelSize();
            QFont font=painter->font();
            font.setPixelSize(static_cast<int>(minWidth));
            painter->save();
            painter->setFont(font);
            QRectF tempRect;
            if(boundingRect().width()<0&& boundingRect().height()<0){
                painter->scale( -1, -1 );
                tempRect=QRectF(-rect().x(),-rect().y(),-rect().width(),-rect().height());
            }
            else if(boundingRect().width()<0){
                painter->scale( -1, 1 );
                tempRect=QRectF(-rect().x(),rect().y(),-rect().width(),rect().height());
            }
            else if(boundingRect().height()<0){
                painter->scale( 1, -1 );
                tempRect=QRectF(rect().x(),-rect().y(),rect().width(),-rect().height());
            }
            else{
                tempRect=rect();
            }
            painter->drawText(tempRect, Qt::AlignVCenter|Qt::AlignLeft, m_textItem->toPlainText());
        }
        painter->restore();
    }
}

void GraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    m_textItem->isHide=false;
    m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->update();
}

