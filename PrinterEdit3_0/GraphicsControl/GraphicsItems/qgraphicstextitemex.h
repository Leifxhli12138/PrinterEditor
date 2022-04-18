#ifndef UTEXTITEM_H
#define UTEXTITEM_H

#include <QTextEdit>

class QGraphicsTextItemEx: public QTextEdit
{
public:
    QGraphicsTextItemEx(const QString &text, QWidget *parent = nullptr);

protected:
    void focusOutEvent(QFocusEvent *event);

};

#endif // UTEXTITEM_H
