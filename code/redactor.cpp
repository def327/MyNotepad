#include "redactor.h"


MyRedactor::MyRedactor(QMainWindow *parent) : QMainWindow(parent)
{
    txt = new NewTextEdit;
    lbl = new QLabel(this);
    bar = new QMenuBar;
    toolbar = new QToolBar;
    statusbar = new QStatusBar;

    file_name_str =""; //default name of a new text document = 0

    ///Make the QMenuBar
    menu = new QMenu("&File");

    menu->addAction("&Open",
                    this,
                    SLOT(do_open()),
                    Qt::CTRL + Qt::Key_O
                    );

    ///--Save
    QAction *act_save = new QAction("&Save",0);
    act_save->setEnabled(false);
    act_save->setShortcut(Qt::CTRL + Qt::Key_S);

    connect(this,
            SIGNAL(allow_save(bool)),
            act_save
            ,SLOT(setEnabled(bool))
            );

    menu->addAction(act_save);

    menu->addAction("&Save_as",this,SLOT(do_save_as()));
    menu->addSeparator();

    ///--Page settings
    QAction *act_page_settings = new QAction ("Page settings",0);
    act_page_settings->setEnabled(false);

    connect(this,
            SIGNAL(allow_page_settings(bool)),
            act_page_settings,
            SLOT(setEnabled(bool))
            );

    connect(act_page_settings,
            SIGNAL(triggered(bool)),
            this,
            SLOT(do_page_settings())
            );

    menu->addAction(act_page_settings);
    menu->addSeparator();

    menu->addAction("Exit",this,SLOT(do_exit()));
    menu2 = new QMenu("&Correction");

    ///--Undo
    QAction *act_undo = new QAction("&Undo",0);
    act_undo->setIcon(QIcon(":/new/prefix1/images/undoPic.png"));
    act_undo->setEnabled(true);

    connect(act_undo,
            SIGNAL(triggered(bool)),
            txt,SLOT(undo())
            );

    menu2->addAction(act_undo);

    ///--Redo
    QAction *act_redo = new QAction("&Redo",0);
    act_redo->setIcon(QIcon(":/new/prefix1/images/redoPic.png"));
    act_undo->setEnabled(true);

    connect(act_redo,
            SIGNAL(triggered(bool)),
            txt,SLOT(redo())
            );

    menu2->addAction(act_redo);

    ///--Copy
    QAction *act_copy = new QAction("&Copy",0);
    act_copy->setShortcut(Qt::CTRL + Qt::Key_C);
    act_copy->setEnabled(false);

    connect(act_copy,
            SIGNAL(triggered(bool)),
            this,
            SLOT(do_copy())
            );

    menu2->addAction(act_copy);

    ///--Paste
    QAction *act_paste = new QAction("&Paste",0);
    act_paste->setShortcut(Qt::CTRL + Qt::Key_C);
    act_paste->setEnabled(false);

    connect(act_paste,
            SIGNAL(triggered(bool)),
            this,SLOT(do_paste())
            );

    menu2->addAction(act_paste);

    ///--Clear
    QAction *act_clear = new QAction("&Clear",0);
    act_clear->setIcon(QIcon(":/new/prefix1/images/RumaxIP Icon 08.png"));
    act_clear->setEnabled(false);

    connect(act_clear,
            SIGNAL(triggered(bool)),
            this,
            SLOT(do_clear())
            );

    menu2->addAction(act_clear);

    ///--Other actions
    menu2->addSeparator();

    menu2->addAction("&Select all",
                     this,
                     SLOT(do_select()),
                     Qt::CTRL + Qt::Key_A
                     );

    menu2->addAction("&Time and Date",this,SLOT(do_time_date()));
    submenu = new QMenu("Help");
    menu2->addMenu(submenu);
    submenu->addAction("About",this,SLOT(do_about()),Qt::Key_F1);

    ///Make Toolbar
    toolbar->addAction(QIcon(":/new/prefix1/images/RumaxIP Icon 11.png"),
                       QString("Open"),
                       this,
                       SLOT(do_open()));

    toolbar->addAction(QIcon(":/new/prefix1/images/RumaxIP Icon 42.png"),
                       QString("Save as"),
                       this,
                       SLOT(do_save_as()));

    toolbar->addAction(QIcon(":/new/prefix1/images/RumaxIP Icon 04.png")
                       ,QString("About"),
                       this,
                       SLOT(do_about()));

    toolbar->addAction(act_clear);
    toolbar->addAction(act_undo);
    toolbar->addAction(act_redo);

    ///Make StatusBar
    statusbar->addWidget(lbl);
    lbl->setText("Lines: " + QString::number(txt->document()->lineCount()));

    ///Сomposition of menus and bars at the main window
    bar->addMenu(menu);
    bar->addMenu(menu2);
    this->setCentralWidget(txt);
    this->setMenuBar(bar);
    this->addToolBar(toolbar);
    this->setStatusBar(statusbar);
    this->setWindowTitle("Application Custom_NOTEPAD");
    this->show();

    ///Requirement slots and signals
    connect(this,
            SIGNAL(set_title(QString)),
            this,
            SLOT(setWindowTitle(QString))
            );

    connect(txt,
            SIGNAL(copyAvailable(bool)),
            act_copy,
            SLOT(setEnabled(bool))
            );

    connect(txt,
            SIGNAL(copyAvailable(bool)),
            act_paste,
            SLOT(setEnabled(bool))
            );

    connect(txt,
            SIGNAL(copyAvailable(bool)),
            act_clear,
            SLOT(setEnabled(bool))
            );

    ///Other slots and signals
    connect(txt,
            SIGNAL(textChanged()),
            this,
            SLOT(do_count_str())
            );

    QFont myfont("TimesNewRoman",14,QFont::Normal);
    txt->setFont(myfont);
}

void MyRedactor::do_open()
{
    file_name_str = QFileDialog::getOpenFileName(0,
                                                 "Open file",
                                                 "",
                                                 "*.txt ;; All files (*.*)"
                                                 );
    if(file_name_str =="")
     {        
        return;
     }    
    QFile file(file_name_str);
    file.open(QIODevice::ReadOnly);
    QTextStream stream_out(&file);
    str=stream_out.readAll();
    txt->setPlainText(str);
    file.close();

    emit allow_save(true);
    emit set_title(file_name_str);
    emit allow_page_settings(true);
}

void MyRedactor::do_save_as()
{
    file_name_str=QFileDialog::getSaveFileName(0,
                                               "Save File",
                                               "New_file.txt",
                                               "*.txt"
                                               );
    if(file_name_str =="")
     {        
        return;
     }
    QFile file(file_name_str);
    file.open(QIODevice::WriteOnly);
    QTextStream stream_in(&file);
    str=txt->toPlainText();
    stream_in<<str;
    file.close();

    emit allow_save(true);
    emit set_title(file_name_str);
    emit allow_page_settings(true);
}

void MyRedactor::do_save()
{
    QFile file2(file_name_str);
    file2.open(QIODevice::WriteOnly);
    QTextStream stream_in(&file2);
    str=txt->toPlainText();
    stream_in<<str;
    file2.close();
}

void MyRedactor::do_page_settings()
{   
    txt->appendPlainText(file_name_str);
}

void MyRedactor::do_exit()
{
    int n = QMessageBox::warning(0,
                                 "Warning!",
                                 "Do you want to save the file?",
                                 QMessageBox::Yes,
                                 QMessageBox::No,
                                 QMessageBox::Cancel
                                 );

    if ( n == QMessageBox::Cancel)
    {
        return;
    }

    if ( n == QMessageBox::Yes)
    {
        do_save_as();
        qApp->quit();
    }

    if( n == QMessageBox::No)
    {
        qApp->quit();
    }
}

void MyRedactor::do_time_date()
{
    QDateTime time;    
    txt->appendPlainText(time.currentDateTime().toString("hh:mm dd.MM.yy"));
}

void MyRedactor::do_select()
{
    txt->selectAll();
}

void MyRedactor::do_copy()
{
    txt->copy();
}

void MyRedactor::do_paste()
{
    txt->paste();
}

void MyRedactor::do_clear()
{
    txt->clear();
}

void MyRedactor::do_about()
{
    QMessageBox::aboutQt(0);
}

void MyRedactor::do_count_str()
{
    lbl->setText("Lines: " + QString::number(txt->document()->lineCount()));
}

void MyRedactor::closeEvent(QCloseEvent *event)
{
    int n = QMessageBox::warning(0,
                                 "Warning!",
                                 "Do you want to save the file?",
                                 QMessageBox::Yes,
                                 QMessageBox::No,
                                 QMessageBox::Cancel
                                 );

    if ( n == QMessageBox::Cancel)
    {
        event->ignore();
        return;
    }

    if ( n == QMessageBox::Yes)
    {
        do_save_as();
        qApp->quit();
    }

}



