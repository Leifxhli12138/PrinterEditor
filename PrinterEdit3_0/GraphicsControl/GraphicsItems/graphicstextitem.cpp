#include "graphicstextitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QTextDocument>

GraphicsTextItem::GraphicsTextItem(const QString &text ,QGraphicsItem *parent)
    :GraphicsItemBase(parent)
{

}

void GraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QRectF r = option->exposedRect;
//    painter->translate(-dd->controlOffset());
//    r.translate(dd->controlOffset());

//    QTextDocument *doc = dd->control->document();
//    QTextDocumentLayout *layout = qobject_cast<QTextDocumentLayout *>(doc->documentLayout());

//    // the layout might need to expand the root frame to
//    // the viewport if NoWrap is set
//    if (layout)
//        layout->setViewport(dd->boundingRect);

//    dd->control->drawContents(painter, r);

//    if (layout)
//        layout->setViewport(QRect());

    painter->restore();
}

