#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Server");

    connect(&server,&tcpserver::tcpServerStatusUpdate,
            this,&Widget::onTcpServerStatusUpdate);
    connect(&server,&tcpserver::tcpServerReceiveMessage,
            this,&Widget::ontcpServerReceiveMessage);

    server.runTcpServer();

}



Widget::~Widget()
{
    delete ui;
}

void Widget::onTcpServerStatusUpdate(QString status)
{
    this->ui->textBrowserServerStatus->append(status);
}

void Widget::ontcpServerReceiveMessage(Message &message)
{
    messageShow(message);
}

void Widget::messageShow(Message &message)
{
    this->ui->textBrowserMessageShow->append(message.getTime().toString());
    this->ui->textBrowserMessageShow->append(message.getSender());
    if(message.gettype() == Message::txt){
        this->ui->textBrowserMessageShow->append(message.getContent());
    }
}


void Widget::on_btnSend_clicked()
{
    Message message;
    QString content = this->ui->textEditMessageInput->toPlainText();
    if(!content.isEmpty()){
        message.setContent(content.toUtf8())->setSender("[Server]")->setTime(QDateTime::currentDateTime())->setType(Message::txt);
        this->ui->textEditMessageInput->clear();
    }
    server.tcpServerSendMessage(message);
    this->messageShow(message);
}


void Widget::on_btnImage_clicked()
{

}

