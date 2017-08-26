#include "sclicklabel.h"
#include <QMouseEvent>

SClickLabel::SClickLabel(QWidget *parent)
    : QLabel(parent)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);

}

SClickLabel::SClickLabel(const QString& text,QWidget *parent)
    : QLabel(parent)
{
    setText(text);
}

void SClickLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}

void SClickLabel::enterEvent(QEvent *)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::blue);
    setPalette(pa);
}

void SClickLabel::leaveEvent(QEvent *)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);
}
