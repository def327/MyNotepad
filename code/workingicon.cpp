#include "workingicon.h"
#include <QtWidgets>

workingIcon::workingIcon(QWidget *parent):QLabel(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    movie=new QMovie(":/new/prefix2/images/free-preloaders11.gif");
    movie->jumpToFrame(movie->frameCount());
    WinMask=movie->currentPixmap();
    setMask(WinMask.mask());
    setMovie(movie);
    movie->start();
}
workingIcon::~workingIcon()
{

}
