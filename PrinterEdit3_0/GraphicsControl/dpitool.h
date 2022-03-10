#ifndef DPITOOL_H
#define DPITOOL_H
#include <QtGlobal>
#include <QApplication>
#include <QScreen>

class  DpiTool{
public :

    qreal getDPI(){
        //获取dpi,dpi:一英寸所占像素长度，一英寸=2.54厘米，96dpi则是的2.54cm=96pix,所以实际1cm=当前屏幕上96/2.54≈37.8pix
        return QApplication::primaryScreen()->logicalDotsPerInch();
    }
    qreal getOneMMPixel(){
        //获取1毫米在屏幕上的像素数
        return QApplication::primaryScreen()->logicalDotsPerInch()/INCH;
    }
    qreal pixelToMM(qreal pixel){
        //像素转毫米
        return pixel*INCH/QApplication::primaryScreen()->logicalDotsPerInch();
    }

private:
    qreal const INCH=25.4;//1英寸=25.4毫米
};

#endif // DPITOOL_H
