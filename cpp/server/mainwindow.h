#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void onNewConnect();//tcp连接
    void onSigWrite(QTcpSocket *socket,const char* str, int len);//tcp写入数据包
private:
    Ui::MainWindow *ui;
    QTcpServer* server;
};

#endif // MAINWINDOW_H
