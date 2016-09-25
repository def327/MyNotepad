#ifndef NEWTEXTEDIT_H
#define NEWTEXTEDIT_H

#include <QtWidgets>

class NewTextEdit : public QPlainTextEdit
{
public:
    explicit NewTextEdit(QPlainTextEdit *parent=0);
protected:
    ///---Реализация своих методов для Drag&Drop QPLainTextEdit
    //virtual void dragEnterEvent(QDragEnterEvent *ev);
    //virtual void dropEvent(QDropEvent *ev);
};

#endif // NEWTEXTEDIT_H


