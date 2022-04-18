#include "qgraphicstextitemex.h"
#include <QTextEdit>
#include <QDebug>
#include <QWidget>
#include <QScrollBar>
#include <QGraphicsProxyWidget>

QGraphicsTextItemEx::QGraphicsTextItemEx(const QString &text, QWidget *parent)
    :QTextEdit (text,parent){

    this->setStyleSheet("background-color: transparent;border:0px;");
    //    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置垂直滚动条样式
    this->verticalScrollBar()->setStyleSheet(
                "QScrollBar::sub-page:vertical,QScrollBar::add-page:vertical{background-color:transparent;}"        /*滚动条滑块背景样式*/
                "QScrollBar::add-line:vertical{background-color:transparent; border:none;}"                         /*滚动条下移按钮样式*/
                "QScrollBar::sub-line:vertical{background-color:transparent; border:none;}"                         /*滚动条上移按钮样式*/
                "QScrollBar::handle:vertical:hover{background-color:rgba(168,168,168,220);}"                         /*鼠标进入*/
                "QScrollBar::handle:vertical{background-color:rgba(168,168,168,170);border-radius:7px;width:13px;}"  /*滚动条滑块样式*/
                "QScrollBar:vertical{margin:0px 0px 0px 0px;background-color:transparent;border:0px;width:14px;}"); /*滚动条整体样式*/

    // "QScrollBar::down-arrow:vertical{border-image:url(:/image/bold.png);width:0px;height:0px;}"         /*滚动条上移图标样式*/
    // "QScrollBar::up-arrow:vertical{ border-image:url(:/image/bold.png);width:0px; height:0px;}"         /*滚动条下移图标样式*/
}

void QGraphicsTextItemEx::focusOutEvent(QFocusEvent *event){
    this->hide();
}
