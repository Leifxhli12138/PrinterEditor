#include "graphicstextitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QAbstractTextDocumentLayout>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>
#include <QImage>
#include <QGraphicsProxyWidget>
#include <QTextEdit>

GraphicsTextItem:: GraphicsTextItem(const QRect & rect ,QString text,QGraphicsItem * parent)
    :GraphicsRectItem(rect,parent)
{
    m_Textwidget=new QGraphicsProxyWidget(this);
    m_text=new QGraphicsTextItemEx("hello");
    m_Textwidget->setWidget(m_text);
    m_text->hide();

    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QRectF  GraphicsTextItem::rect(){
    return boundingRect();
}
void GraphicsTextItem::multipleChoiceEvent(){
    this->uncheckedEvent();
}
void GraphicsTextItem::uncheckedEvent(){
    m_text->hide();
}
void GraphicsTextItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point){
    GraphicsRectItem::resizeTo(dir, point);
    if(m_Textwidget->isVisible())
        this->uncheckedEvent();

    if(SizeHandleRect::Rotate!=dir)
        //重新设置内置textEdit大小
        m_text->resize(abs(rect().width()),abs(rect().height()));
}

void GraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(m_Textwidget!=nullptr&&!m_Textwidget->isVisible()){
        qreal textItemX=rect().x();
        qreal textItemY=rect().y();
        if(rect().width()<0)
            textItemX+=rect().width();
        if(rect().height()<0)
            textItemY+=rect().height();
        if(!rect().height()||!rect().width())return;
        //设置textBox新坐标
        m_Textwidget->setPos(QPointF(textItemX,textItemY));

        //多行文本绘制
        QFontMetrics metrics(painter->font());
        QStringList texts=m_text->toPlainText().split("\n");

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
            painter->drawText(tempRect, Qt::AlignVCenter|Qt::AlignLeft, m_text->toPlainText());
        }
        painter->restore();
    }
}

void GraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    m_Textwidget->show();
    this->update();
}

