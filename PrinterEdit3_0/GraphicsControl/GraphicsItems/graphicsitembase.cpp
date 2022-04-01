#include "GraphicsItemBase.h"
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QCursor>
#include <QDebug>
#include <QGraphicsEffect>
#include <QMenu>
#include <qmath.h>
#include <QGraphicsView>
#include "GraphicsControl\Enums.h"
#include "GraphicsControl\sizehandle.h"


//返回轮廓
QPainterPath GraphicsItemBase::qt_graphicsItem_shapeFromPath(const QPainterPath &path, const QPen &pen) const
{
    //QPainterPathStroker设置宽度为1.0
    // We unfortunately need this hack as QPainterPathStroker will set a width of 1.0
    // if we pass a value of 0.0 to QPainterPathStroker::setWidth()
    const qreal penWidthZero = qreal(0.00000001);

    if (path == QPainterPath() || pen == Qt::NoPen)
        return path;
    QPainterPathStroker ps;
    ps.setCapStyle(pen.capStyle());
    if (pen.widthF() <= 0.0)
        ps.setWidth(penWidthZero);
    else
        ps.setWidth(pen.widthF());
    ps.setJoinStyle(pen.joinStyle());
    ps.setMiterLimit(pen.miterLimit());
    QPainterPath p = ps.createStroke(path);
    p.addPath(path);
    return p;
}


GraphicsItemBase::GraphicsItemBase(QGraphicsItem *parent)
    :QAbstractGraphicsShapeItem(parent)
{
}

//设置锚点位置
void GraphicsItemBase::updateGeometry()
{
    const QRectF &geom = this->boundingRect();
    const int w = SELECTION_HANDLE_SIZE;
    const int h = SELECTION_HANDLE_SIZE;
    const int wHalf = w>>1;
    const int hHalf = h>>1;

    const Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it) {
        SizeHandleRect *hndl = *it;;
        switch (hndl->dir()) {
        case SizeHandleRect::LeftTop:
            hndl->setPos(geom.x() - wHalf, geom.y() - hHalf);
            break;
        case SizeHandleRect::Top:
            if( geom.width()>0){
                hndl->setRect(0,0,geom.width()-w,h);
                hndl->setPos(geom.x()+ wHalf , geom.y() - hHalf );
            }else{
                hndl->setRect(0,0,geom.width()+w,h);
                hndl->setPos(geom.x()- wHalf , geom.y() - hHalf );
            }
            break;
        case SizeHandleRect::RightTop:
            hndl->setPos(geom.x() + geom.width() - wHalf, geom.y() - hHalf);
            break;
        case SizeHandleRect::Right:
            if( geom.height()>0){
                hndl->setRect(0,0,w, geom.height()-h);
                hndl->setPos(geom.x() + geom.width() - wHalf , geom.y() + hHalf  );
            }else{
                hndl->setRect(0,0,w, geom.height()+h);
                hndl->setPos(geom.x() + geom.width() - wHalf , geom.y() - hHalf  );
            }
            break;
        case SizeHandleRect::RightBottom:
            hndl->setPos(geom.x() + geom.width() -wHalf, geom.y() + geom.height() - hHalf);
            break;
        case SizeHandleRect::Bottom:
            if( geom.width()>0){
                hndl->setRect(0,0,geom.width()-w,h);
                hndl->setPos(geom.x()+ wHalf, geom.y() + geom.height() - hHalf );
            }else{
                hndl->setRect(0,0,geom.width()+w,h);
                hndl->setPos(geom.x()- wHalf, geom.y() + geom.height() - hHalf );
            }
            break;
        case SizeHandleRect::LeftBottom:
            hndl->setPos(geom.x() - wHalf, geom.y() + geom.height() - hHalf);
            break;
        case SizeHandleRect::Left:
            if( geom.height()>0){
                hndl->setRect(0,0,w, geom.height()-h);
                hndl->setPos(geom.x() - wHalf, geom.y() + hHalf );
            }
            else{
                hndl->setRect(0,0,w, geom.height()+h);
                hndl->setPos(geom.x() - wHalf, geom.y()- hHalf );
            }
            break;
        case SizeHandleRect::Rotate:
            if( geom.height()>0)
                hndl->setPos(geom.center().x()  - wHalf , geom.y() - hHalf -(30));
            else
                hndl->setPos(geom.center().x()  - wHalf , geom.y()+geom.height() - hHalf -(30) );
            break;
        default:
            break;
        }
    }
}

void GraphicsItemBase::setState(SelectionHandleState st)
{
    const Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
        (*it)->setState(st);
}

//锚点鼠标样式交互
SizeHandleRect::Direction GraphicsItemBase::hitTest(const QPointF &point) const
{
    const Handles::const_iterator hend =  m_handles.end();
    for (Handles::const_iterator it = m_handles.begin(); it != hend; ++it)
    {
        if ((*it)->hitTest(point) ){
            return (*it)->dir();
        }
    }
    return SizeHandleRect::None;
}

Qt::CursorShape GraphicsItemBase::getCursor(SizeHandleRect::Direction dir, QPointF point)
{
    const qreal geomCenterX =pos().x()+ boundingRect().center().x();
    const qreal geomCenterY =pos().y()+ boundingRect().center().y();
    //根据鼠标位置重新计算应返回的鼠标样式
    switch (dir) {
    case SizeHandleRect::LeftTop:
    case SizeHandleRect::RightTop:
    case SizeHandleRect::RightBottom:
    case SizeHandleRect::LeftBottom:
        if(point.x()>geomCenterX && point.y()>geomCenterY)
            dir=SizeHandleRect::RightBottom;
        else if(point.x()>geomCenterX && point.y()<geomCenterY)
            dir=SizeHandleRect::RightTop;
        else if(point.x()<geomCenterX && point.y()>geomCenterY)
            dir=SizeHandleRect::LeftBottom;
        else if(point.x()<geomCenterX && point.y()<geomCenterY)
            dir=SizeHandleRect::LeftTop;
        break;
    default:break;
    }

    switch (dir) {
    case SizeHandleRect::Right:
        return Qt::SizeHorCursor;
    case SizeHandleRect::RightTop:
        return Qt::SizeBDiagCursor;
    case SizeHandleRect::RightBottom:
        return Qt::SizeFDiagCursor;
    case SizeHandleRect::LeftBottom:
        return Qt::SizeBDiagCursor;
    case SizeHandleRect::Bottom:
        return Qt::SizeVerCursor;
    case SizeHandleRect::LeftTop:
        return Qt::SizeFDiagCursor;
    case SizeHandleRect::Left:
        return Qt::SizeHorCursor;
    case SizeHandleRect::Top:
        return Qt::SizeVerCursor;
    case SizeHandleRect::Rotate:
        return Qt::PointingHandCursor;
    default:
        return Qt::ArrowCursor;
    }
}

void GraphicsItemBase::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{
    //计算正常旋转角度（0度）下，中心的的坐标
    auto oldCenter=QPointF(x()+rect().x()+rect().width()/2,y()+rect().y()+rect().height()/2);
    //计算旋转后，中心坐标在view中的位置
    auto newCenter= mapToScene(rect().center());
    //设置正常坐标减去两个坐标的差
    auto difference=oldCenter-newCenter;
    setPos(x()-difference.x(),y()-difference.y());
    //最后设置旋转中心
    setTransformOriginPoint(rect().center());
}

void GraphicsItemBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *moveAction = menu.addAction("move back");
    QAction *actAction = menu.addAction("test");
    QAction *selectedAction = menu.exec(event->screenPos());
    if(selectedAction == moveAction) {
        setPos(0, 0);
    }
}

QVariant GraphicsItemBase::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //选中时
    if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
        //        qDebug()<<" Item Selected : " << value.toString();
        setState(value.toBool() ? SelectionHandleActive : SelectionHandleOff);
    }else if ( change == QGraphicsItem::ItemRotationHasChanged ){
        //        qDebug()<<"Item Rotation Changed:" << value.toString();
    }else if ( change == QGraphicsItem::ItemTransformOriginPointHasChanged ){
        //        qDebug()<<"ItemTransformOriginPointHasChanged:" << value.toPointF();
    }
    return value;
}
//记录按下旋转按钮时的坐标
void GraphicsItemBase::setRotateStart(QPointF point ){
    m_mouseRotateStart=point;
    m_fLastAngle=rotation();

}
void GraphicsItemBase::setRotateEnd(QPointF point)
{
    QPointF ori = mapToScene(transformOriginPoint());
    QPointF v1 = m_mouseRotateStart - ori;
    QPointF v2 = point - ori;
    //θ=atan2(v2.y,v2.x)−atan2(v1.y,v1.x)
    qreal angle =atan2f(v2.y(), v2.x()) - atan2f(v1.y(), v1.x());

    angle =m_fLastAngle+ angle * 180 / 3.1415926;
    m_angle= angle;
    setRotation(angle);
}
