#ifndef SCLICKLABEL_H
#define SCLICKLABEL_H

#include <QWidget>
#include <QLabel>

//label单击事件类
class SClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SClickLabel(QWidget *parent = 0);
    SClickLabel(const QString& text,QWidget *parent = 0);
signals:
    void clicked();
protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
public slots:
};

#endif // SCLICKLABEL_H
