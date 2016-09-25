#include "redactor.h"
#include "workingicon.h"


void loadModules(workingIcon *sh_screen)
{
   QTime time;
   time.start();
   for (int i=0;i< 100;)
   {
        if(time.elapsed() > 20)
        {
            time.start();
            ++i;
        }        
        qApp->processEvents();        
   }
   sh_screen->hide();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ///Загрузка заставки программы
    workingIcon  splash;
    splash.show();
    loadModules(&splash);
    ///-----------------------------

    MyRedactor *my = new MyRedactor;
    QApplication::setStyle(QStyleFactory::create("fusion"));    
    my->resize(800,400);
    my->show();

    return a.exec();
}
