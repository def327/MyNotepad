#ifndef WORKINGICON
#define WORKINGICON

#include <QtWidgets>

class workingIcon:public QLabel
{
  public:
    workingIcon(QWidget *parent=0);
    ~workingIcon();

  private:
    QMovie *movie;
    QPixmap WinMask;
};





#endif // WORKINGICON

