#ifndef UGRAPHICSSCENE_H
#define UGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "Enums.h"
#include "ugraphicsview.h"
#include "dpitool.h"
#include <QMargins>
#include  "GraphicsControl/sizehandle.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

using namespace PrinterEdit3_0;

class UGraphicsScene : public QGraphicsScene,public DpiTool
{
    Q_OBJECT
signals:
    void initSizeOverEvent();
    void rluerDispalyItemPoint();
public:
    explicit UGraphicsScene(QObject *parent = 0);
    void createArea(qreal x, qreal y, qreal w, qreal h);
    void createArea(QRectF rectF);
    QMargins* getMargin(){return m_magin;}
    UGraphicsView* getFirstView();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event)Q_DECL_OVERRIDE;
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    QMargins* m_magin;
    void multipleChoiceEvent();
private:
    void mousePressDrawItem(QGraphicsSceneMouseEvent* event);
    void mouseMoveDrawItem(QGraphicsSceneMouseEvent* event);
    void mouseReleaseDrawItem(QGraphicsSceneMouseEvent* event);
    void mousePressSelectItem(QGraphicsSceneMouseEvent* event);
    void mouseMoveSelectItem(QGraphicsSceneMouseEvent* event);
    void mouseReleaseSelectItem(QGraphicsSceneMouseEvent* event);
public:
     QAbstractGraphicsShapeItem * item;

    QPointF c_down;
    QPointF c_last;
    static ItemShape c_drawShape;

    bool m_hoverSizer=false;

    static SelectMode m_selectMode;
    static SizeHandleRect::Direction nDragHandle ;
};

#endif // UGRAPHICSSCENE_H
