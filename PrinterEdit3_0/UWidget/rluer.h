#ifndef RLUER_H
#define RLUER_H

#include <QWidget>
#include "GraphicsControl/ugraphicsview.h"
#include "GraphicsControl/ugraphicsscene.h"

namespace Ui {
class Rluer;
}

class Rluer : public QWidget
{
    Q_OBJECT

public:
    explicit Rluer(QWidget *parent = nullptr);
    ~Rluer();
    UGraphicsView* getView();
    void setOffsetX(qreal value) {
        offsetX = value;
        update();
    }
    void setOffsetY(qreal value) {
        offsetY = value;
        update();
    }
public slots:
    void updateOffset();
private:
    Ui::Rluer *ui;

    UGraphicsScene * m_scene;
    qreal offsetX{0};
    qreal offsetY{0};
    //画尺子所需变量start
    int cm=10;
    int cmHalf=5;
    int m_rluerHeight=60;
    int RluerHeightHalf=m_rluerHeight>>1;
    int RluerHeightHalfHalf=RluerHeightHalf>>1;
    //画尺子所需变量end
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
private:
    void drawRluer(QPainter* painter);
    void drawSelectedElement(QPainter* painter);


};

#endif // RLUER_H
