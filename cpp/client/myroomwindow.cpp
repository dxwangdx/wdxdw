#include "myroomwindow.h"
#include "ui_myroomwindow.h"
#include "videosurface.h"
#include <QDateTime>
#include <QMessageBox>

MyRoomWindow::MyRoomWindow(QTcpSocket* socket,QWidget *parent) :
    QMainWindow(parent),socket(socket),
    ui(new Ui::MyRoomWindow)
{
    ui->setupUi(this);
}

MyRoomWindow::~MyRoomWindow()
{
    delete ui;
}

//关闭事件
void MyRoomWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    QWidget *parent = this->parentWidget();
    if(0!=parent){
        package pack;
        memset(&pack,0,sizeof(package));
        pack.type = EXIT_ROOM;
        strncpy(pack.name,this->getName(),20);
        strncpy(pack.roomName,this->getRoomName(),20);
        socket->write((char*)&pack,sizeof(pack));
        camera->stop();
    }
}

//设置用户名
void MyRoomWindow::setName(const char* name)
{
    strncpy(this->name,name,20);
}

//设置房间名
void MyRoomWindow::setRoomName(const char* name)
{
    strncpy(this->roomName,name,20);
}

//设置端口号
void MyRoomWindow::setPort(int port)
{
    this->port = port;
}

//获取用户名
const char* MyRoomWindow::getName() const
{
    return name;
}

//获取房间名
const char* MyRoomWindow::getRoomName() const
{
    return roomName;
}

//获取端口号
int MyRoomWindow::getPort() const
{
    return port;
}

//刷新房间成员按钮
void MyRoomWindow::on_btn_refresh_clicked()
{
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = PERSON_REFRESH;
    strcpy(pack.name,getRoomName());
    socket->write((char*)&pack,sizeof(pack));
}

//获取房间成员信息
void MyRoomWindow::refreshPersonList(package pack)
{
    if(strcmp(pack.message,"refresh") == 0)
    {
        ui->te_member->clear();
    }
    else
    {
        QString str = QString::fromLocal8Bit(pack.name);
        ui->te_member->append(str);
    }
}

//开启视频
void MyRoomWindow::openCamera()
{
    //开启摄像头
    QCameraInfo info = QCameraInfo::defaultCamera ();
    camera = new QCamera(info, this);
    VideoSurface *vf = new VideoSurface(this);
    camera->setViewfinder (vf);
    QObject::connect (vf, SIGNAL(videoChanged(QVideoFrame)),
             this, SLOT(onvideoChanged(QVideoFrame)));

    //建立udp网络连接
    socketWrite = new QUdpSocket(this);
    socketRead = new QUdpSocket(this);
    //groupAddress.setAddress ("224.0.1.200");
    groupAddress.setAddress ("239.88.88.88");   //组播地址
    socketWrite->setSocketOption (QAbstractSocket::MulticastTtlOption,1);//设置套接字属性
    socketRead->bind (QHostAddress::AnyIPv4, this->getPort(), QUdpSocket::ReuseAddressHint|QUdpSocket::ShareAddress);//绑定组播地址端口
    socketRead->joinMulticastGroup (groupAddress);  //添加到组播，绑定到读套接字上

    //udp读写
    QObject::connect (socketRead, SIGNAL(readyRead()),this, SLOT(UdpReadRead()));

    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(onTime()));
}

//发送消息
void MyRoomWindow::on_btn_send_clicked()
{
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = SEND_MESSAGE;
    QString message = ui->le_message->text();
    if(message.isEmpty())
    {
        QMessageBox::warning(this,"warning","消息不能为空！！！");
        return;
    }
    const char *messageP = message.toLocal8Bit().data();
    strncpy(pack.name,this->getName(),20);
    strncpy(pack.roomName,this->getRoomName(),20);
    strncpy(pack.message,messageP,1024);

    ui->le_message->setFocus();
    ui->le_message->clear();

    socket->write((char*)&pack,sizeof(pack));
}

//接收消息
void MyRoomWindow::reveiceMessage(package pack)
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString sttr = time.toString("yyyy-MM-dd hh:mm:ss dddd");//设置系统时间显示格式
    ui->te_record->append(sttr);//显示时间

    QString str1 = QString::fromLocal8Bit(pack.name);
    QString str2 = QString::fromLocal8Bit(pack.message);
    QString str = str1 + ": " + str2;
    ui->te_record->append(str);
}

//开启摄像头
void MyRoomWindow::on_btn_camera_open_clicked()
{

    if(strcmp(this->getName(),this->getRoomName()) == 0){
        camera->start();
    }
    else
    {
        QMessageBox::warning (this, "warning", "只有房主可以开启直播");
    }
}

//关闭摄像头
void MyRoomWindow::on_btn_camera_close_clicked()
{
    camera->stop();
    ui->lb_video->clear();
}

//发送弹幕
void MyRoomWindow::on_btn_bs_send_clicked()
{
    package pack;
    memset(&pack,0,sizeof(package));
    pack.type = SEND_BS;
    QString message = ui->le_message->text();
    if(message.isEmpty())
    {
        QMessageBox::warning(this,"warning","弹幕不能为空！！！");
        return;
    }
    const char *messageP = message.toLocal8Bit().data();
    strncpy(pack.name,this->getName(),20);
    strncpy(pack.roomName,this->getRoomName(),20);
    strncpy(pack.message,messageP,1024);
    socket->write((char*)&pack,sizeof(pack));
}

//弹幕信息显示
void MyRoomWindow::textScroll(package pack)
{
    QString bs_text = pack.message;
    label = new QLabel(bs_text, ui->textscroll);
    label->setStyleSheet("color:red");
    label->setFont(QFont("Timer",28,QFont::Bold));
    int len = qrand()% ui->textscroll->height() + 0;
    label->move(0,len);
    label->adjustSize();
    timer->start(10);
}

//定时器槽函数 移动弹幕信息
void MyRoomWindow::onTime()
{
    const QPoint& p = label->pos();
    if(p.x() < (ui->textscroll->width()))
    {
        label->move(p.x() + 1, p.y());
        label->show();
        label->update();
    }
    else
    {
        label->hide();
    }
}

/*
函数功能：udp接收图片
参数：无
返回值：无
*/
void MyRoomWindow::UdpReadRead()
{
    static QByteArray *imageBytes = new QByteArray(2280000,0);//字符数组2280000字节，初始化为0
    static QDataStream *dataStream = new QDataStream(imageBytes,QIODevice::ReadWrite);//数据流指针指向数组的首地址，以读写格式
    //static int readed = 0;
    while(socketRead->hasPendingDatagrams())//udp下判断是否还有待读取的数据包，有返回true，无返回false
    {
        ImagePackage pack;
        memset(&pack,0,sizeof(ImagePackage));
        socketRead->readDatagram((char*)&pack,sizeof(ImagePackage));
        if(true == pack.isLastPack)
        {
//            qDebug()<<"packTaken:"<<pack.packTaken;
            dataStream->writeRawData(pack.data,pack.packTaken);
            QImage image = QImage((uchar*)imageBytes->data(),pack.width,pack.height,pack.bytesPerline,QImage::Format_RGB32);

            QPixmap map = QPixmap::fromImage(image);//把image转化为map
 //           qDebug()<<"接收的图片大小:"<<image.byteCount();
 //           qDebug()<<"width"<<pack.width;
 //           qDebug()<<"height"<<pack.height;
 //           qDebug()<<"bytesPerline"<<pack.bytesPerline;

            map = map.scaled(ui->lb_video->size());
            ui->lb_video->setPixmap(map);//显示图片
            dataStream->device()->seek(0);

        }
        else
        {
            dataStream->writeRawData(pack.data,pack.packTaken);
        }
    }
}

/*
函数功能：获取视频采集的图片并通过udp发送出去
参数：QVideoFrame curFrame
返回值：无
*/
void MyRoomWindow::onvideoChanged(QVideoFrame curFrame)
{
    static int i = 0;
    i++;
    int unitBytes = 4096;
    QVideoFrame frame(curFrame);
    frame.map(QAbstractVideoBuffer::ReadOnly);
    //通过QVideoFrame对象构建QImage对象
    QImage image(frame.bits(),frame.width(),frame.height(),QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
    //将图像旋转180
    QMatrix matrix;
    matrix.rotate(180);
    image = image.transformed(matrix);

    //显示图片
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.scaled(ui->lb_video->size());
    ui->lb_video->setPixmap(pixmap);

    if(i % 4 != 0)
    {
        return;
    }
    int byteCount = image.byteCount();//图片大小
    int width = image.width();
    int height = image.height();
    int bytePerLine = image.bytesPerLine();//每行字节数
//    qDebug()<<"byteCount:"<<byteCount;
//    qDebug()<<"width:"<<width;
//    qDebug()<<"height:"<<height;
//    qDebug()<<"bytePerLine:"<<bytePerLine;
    int writeBytes = 0;
    while(true)
    {
        ImagePackage pack;
        memset(&pack,0,sizeof(ImagePackage));
        pack.width = width;
        pack.height = height;
        pack.bytesPerline = bytePerLine;
        if(writeBytes<byteCount)
        {
            memcpy(pack.data,(char*)image.bits()+writeBytes,unitBytes);
            pack.packTaken = unitBytes;
            writeBytes += unitBytes;
            if(writeBytes>=byteCount)
            {
                pack.isLastPack = true;
                pack.packTaken = unitBytes-writeBytes+byteCount;
//                qDebug()<<"writeBytes:"<<writeBytes;
            }
            else
            {
                pack.isLastPack = false;
                pack.packTaken = unitBytes;
            }
            socketWrite->writeDatagram((char*)&pack,sizeof(ImagePackage),QHostAddress::Broadcast,this->getPort());//udp写入
        }
        else
        {
            break;
        }
    }
}

