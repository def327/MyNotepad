#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "newtextedit.h"


class MyRedactor : public QMainWindow
{
    Q_OBJECT    
private:

    ///--Functional items
    NewTextEdit *txt;
    QLabel *lbl;

    ///--Menu and bar
    QMenuBar *bar;
    QMenu *menu;
    QMenu *menu2;
    QMenu *submenu;
    QToolBar *toolbar;
    QStatusBar *statusbar;

    ///--Сontainer for open/save
    QString str;
    QString file_name_str;

public:
    explicit MyRedactor(QMainWindow *parent = 0);

signals:    
    void set_title(QString);
    void allow_copy(bool);
    void allow_paste(bool);
    void allow_clear(bool);
    void allow_save(bool);
    void allow_page_settings(bool);

protected:
    void closeEvent(QCloseEvent *);

public  slots:

    ///--Slots for menu
    void do_open();
    void do_save_as();
    void do_save();
    void do_page_settings();
    void do_exit();
    void do_time_date();

    ///--Slots for menu2
    void do_select();
    void do_copy();
    void do_paste();
    void do_clear();
    void do_about();

    ///--Other Slots
    void do_count_str();
};

#endif // WIDGET_H
