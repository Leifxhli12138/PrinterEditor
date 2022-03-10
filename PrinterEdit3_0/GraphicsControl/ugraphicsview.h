#ifndef UGRAPHICSVIEW_H
#define UGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include "dpitool.h"

class UGraphicsView : public QGraphicsView,public DpiTool
{
    Q_OBJECT
public:
    explicit UGraphicsView(QWidget *parent = nullptr);
    void ZoomOut();
    void ZoomIn();
    QSizeF getSize();
    qreal const MAX_SCALE=10;
    qreal const MIN_SCALE=0.1;
    qreal scaleValue(){
        return m_d_scaleValue;
    };
signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
private:
    qreal m_d_scaleValue;  // 缩放值
    qreal m_d_zoomDelta;  // 缩放的增量
    void zoom(qreal scaleFactor);
public:

};

#endif // UGRAPHICSVIEW_H
