#ifndef ENROLLWINDOW_H
#define ENROLLWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "package.h"
#include <string.h>
#include <QMessageBox>
#include <QTcpSocket>

//注册界面
namespace Ui {
class EnrollWindow;
}

class EnrollWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EnrollWindow(QTcpSocket* socket,QWidget *parent = 0);
    ~EnrollWindow();
protected:
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void on_btn_return_clicked();
    void on_btn_ensure_clicked();

private:
    QTcpSocket* socket;
    Ui::EnrollWindow *ui;
};

#endif // ENROLLWINDOW_H
