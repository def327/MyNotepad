#include "newtextedit.h"

NewTextEdit::NewTextEdit(QPlainTextEdit *parent):QPlainTextEdit(parent)
{
    //setAcceptDrops(true);
}

/*
void NewTextEdit::dragEnterEvent(QDragEnterEvent *ev)
{
    if(ev->mimeData()->hasText())
    {
        ev->acceptProposedAction();
    }
}

void NewTextEdit::dropEvent(QDropEvent *ev)
{
    this->appendPlainText(ev->mimeData()->text());

}
*/
