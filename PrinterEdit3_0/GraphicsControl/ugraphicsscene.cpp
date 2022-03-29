#include <QObject>
#include "ugraphicsscene.h"
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsRectItem>
#include <QDebug>
#include <QGraphicsView>
#include "ugraphicsview.h"
#include <QScreen>
#include <QMargins>
#include <GraphicsControl/GraphicsItems/graphicsitembase.h>
#include "GraphicsControl/GraphicsItems/graphicsrectitem.h"
#include "GraphicsControl/GraphicsItems/graphicstextitem.h"
#include "GraphicsControl/GraphicsItems/graphicsellipseitem.h"
#include <QGraphicsTextItem>

ItemShape UGraphicsScene::c_drawShape = ItemShape::selection;
SelectMode UGraphicsScene::m_selectMode=SelectMode::none;
SizeHandleRect::Direction UGraphicsScene::nDragHandle = SizeHandleRect::None;

UGraphicsScene::UGraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{
    m_magin=new QMargins(10,10,10,10);//设置边距，单位像素
    installEventFilter(this); //安装事件过滤器
}

//获取首个视图
UGraphicsView* UGraphicsScene::getFirstView(){
    if(this->views().count()>0)
        return static_cast<UGraphicsView*>(this->views().first());
    else
        throw "Scene视图是空的";
}

//以毫米为单位，创建活动区域
void UGraphicsScene::createArea(qreal x, qreal y, qreal w, qreal h){
    this->createArea(QRectF(x,y,w,h));
}

//以毫米为单位，创建活动区域
void UGraphicsScene::createArea(QRectF rectF){
    qreal pixel=getOneMMPixel();
    qreal width=rectF.width()*pixel+m_magin->left()+m_magin->right();
    qreal height=rectF.height()*pixel+m_magin->top()+m_magin->bottom();
    this->setSceneRect(QRectF(rectF.x()*pixel,rectF.y()*pixel,width,height));

    emit this->initSizeOverEvent();
}

void UGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event){
    QGraphicsScene::wheelEvent(event);
    this->update();
}

void UGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect){
    QPainterPath path;
    path.addRoundedRect(this->sceneRect().adjusted(m_magin->left(),m_magin->top(),-m_magin->right(),-m_magin->bottom()), 10, 10);
    painter->fillPath(path, Qt::white);
    QGraphicsScene::drawBackground(painter,rect);
}

void UGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit rluerDispalyItemPoint();

    //create obj
    if(c_drawShape != ItemShape::selection){
        this->mousePressDrawItem(event);
    }
    else{
        this->mousePressSelectItem(event);
    }


}

void UGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        emit rluerDispalyItemPoint();
    }

    this->mouseMoveSelectItem(event);

}

void UGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(c_drawShape != ItemShape::selection) {
        this->mouseReleaseDrawItem(event);
    }
    else{
        this->mouseReleaseSelectItem(event);
    }
}

bool UGraphicsScene::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::Enter){ //当鼠标进入时
        if(c_drawShape != ItemShape::selection)
            getFirstView()->setCursor(Qt::CrossCursor);
        else
            getFirstView()->setCursor(Qt::ArrowCursor);
    }
    else if(event->type() == QEvent::Leave){//当鼠标离开时
        getFirstView()->setCursor(Qt::ArrowCursor);
    }
    QGraphicsScene::eventFilter(watched,event);
}

//mouse draw item
void UGraphicsScene::mousePressDrawItem(QGraphicsSceneMouseEvent* event){
    c_down = event->scenePos();
    c_last = event->scenePos();

    clearSelection();
    item=nullptr;
    switch ( c_drawShape ){
    case ItemShape::rectangle:
        item = new GraphicsRectItem(QRect(0,0,0,0),nullptr);
        item->setPen(Qt::NoPen);
        break;
    case ItemShape::ellipse:
        item = new GraphicsEllipseItem(QRect(0,0,0,0),nullptr);
        item->setPen(Qt::NoPen);
        break;
    case ItemShape::line:
        //        item = new GraphicsTextItem(QRect(0,0,0,0),"hello",nullptr);
        //        item->setPen(Qt::NoPen);
        break;
    case ItemShape::text:
        item = new GraphicsTextItem(QRect(0,0,0,0),"hello",nullptr);
        item->setPen(Qt::NoPen);
        break;
    }
    if ( item == nullptr) return;
    item->setPos(event->scenePos());
    this->addItem(item);
    item->setSelected(true);
    m_selectMode = SelectMode::size;
    nDragHandle = SizeHandleRect::RightBottom;
}
void UGraphicsScene::mouseMoveDrawItem(QGraphicsSceneMouseEvent* event){
    this->mouseMoveSelectItem(event);
}

void UGraphicsScene::mouseReleaseDrawItem(QGraphicsSceneMouseEvent* event){
    if ( event->scenePos() == c_down ){
        if ( item != nullptr)
            this->removeItem(item);
        this->mousePressSelectItem(event);
    }
    this->mouseReleaseSelectItem(event);
}

//mouse select item
void UGraphicsScene::mousePressSelectItem(QGraphicsSceneMouseEvent* event){
    c_down = event->scenePos();
    c_last = event->scenePos();

    this->setFocus();
    if (!m_hoverSizer)
        QGraphicsScene::mousePressEvent(event);

    m_selectMode = SelectMode::none ;
    QList<QGraphicsItem *> items = this->selectedItems();
    GraphicsItemBase *item = nullptr;

    if ( items.count() == 1 )
    {
        item = qgraphicsitem_cast<GraphicsItemBase*>(items.first());
    }
    if ( item != nullptr ){

        nDragHandle = item->hitTest(event->scenePos());
        if ( nDragHandle !=SizeHandleRect::None)
        {
            if(nDragHandle==SizeHandleRect::Rotate)
                m_selectMode=SelectMode::rotate;
            else
                m_selectMode = SelectMode::size;
            //旋转or改变size时触发
            item->setRotateStart(event->scenePos());//更新旋转坐标,此步非常重要，否则会引起QGraphicsItem旋转后，改变大小会让item平移
        }
        else
            m_selectMode = SelectMode::move;
        //        m_lastSize = item->boundingRect().size();
    }
    //==============画框选框
    if( m_selectMode ==SelectMode::none  ){
        m_selectMode = SelectMode::netSelect;
        getFirstView()->setDragMode(QGraphicsView::RubberBandDrag);

    }
}

void UGraphicsScene::mouseMoveSelectItem(QGraphicsSceneMouseEvent* event){
    c_last = event->scenePos();

    bool isGroup = false;
    QList<QGraphicsItem *> items = this->selectedItems();
    GraphicsItemBase * item = nullptr;
    if ( items.count() == 1 ){

        item = qgraphicsitem_cast<GraphicsItemBase*>(items.first());
        if ( item != nullptr ){
            if ( nDragHandle != SizeHandleRect::None &&( m_selectMode == SelectMode::size || m_selectMode == SelectMode::rotate)){
                // "按住拉伸ing";
                item->resizeTo(nDragHandle,c_last);
            }
            else if(nDragHandle == SizeHandleRect::None && m_selectMode == ItemShape::selection ){
                SizeHandleRect::Direction handl= item->hitTest(event->scenePos());
                if(handl!=SizeHandleRect::None){
                    m_hoverSizer=true;
                    if(c_drawShape == ItemShape::selection)//没有选择绘制图形时
                        getFirstView()->setCursor(item->getCursor(handl,event->scenePos()));
                    else
                        getFirstView()->setCursor(Qt::CrossCursor);
                }
                else {
                    m_hoverSizer=false;
                    if(c_drawShape == ItemShape::selection)//没有选择绘制图形时
                        getFirstView()->setCursor(Qt::ArrowCursor);
                    else
                        getFirstView()->setCursor(Qt::CrossCursor);
                }
            }
        }
        //        QGraphicsItemGroup *item1 = qgraphicsitem_cast<QGraphicsItemGroup*>(items.first());
        //        if ( item1 != nullptr ){
        //            isGroup = true;
        //        }
    }

    if ( (m_selectMode != SelectMode::size  && items.count() >= 1) || isGroup )
    {
        QGraphicsScene::mouseMoveEvent(event);
    }
}
void UGraphicsScene::mouseReleaseSelectItem(QGraphicsSceneMouseEvent *event){
    if (event->scenePos() == c_down)
        c_drawShape = ItemShape::selection;

    if (m_selectMode == SelectMode::netSelect ){
        getFirstView()->setDragMode(QGraphicsView::NoDrag);
    }

    m_selectMode = SelectMode::none ;
    nDragHandle = SizeHandleRect::None;
    m_hoverSizer = false;

    QGraphicsScene::mouseReleaseEvent(event);
}
