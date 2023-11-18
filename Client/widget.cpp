#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Client");

    connect(&socket,&tcpsocket::socketReceiveMessage,
            this,&Widget::onSocketReceiveMessage);

    socket.runTcpSocket();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onSocketReceiveMessage(Message &message)
{
    messageShow(message);
}

void Widget::messageShow(Message &message)
{
    this->ui->textBrowseMessageShow->append(message.getTime().toString());
    this->ui->textBrowseMessageShow->append(message.getSender());
    if(message.gettype() == Message::txt){
        this->ui->textBrowseMessageShow->append(message.getContent());
    }
}

void Widget::on_btnSend_clicked()
{
    Message message;
    QString content = this->ui->textEditInput->toPlainText();
    if(!content.isEmpty()){
        message.setContent(content.toUtf8())->setSender("[Client]")->setTime(QDateTime::currentDateTime())->setType(Message::txt);
        this->ui->textEditInput->clear();
    }
    this->socket.messageSend(message);
    this->messageShow(message);
}


void Widget::on_btnImage_clicked()
{

}


void Widget::on_btnDisconnect_clicked()
{
    QMessageBox::information(this,"Tips","DisConnected Successfully");
    this->socket.disconnect();
    this->ui->labelCurrentIPAdd->setText("NULL");
}


void Widget::on_btnConnect_clicked()
{
    this->ipinput->show();
    QString ip = this->ipinput->getIp();
    if(!ip.isEmpty()){
        this->socket.tcpConnect(ip);
        this->ui->labelCurrentIPAdd->setText(ip);
    }
}

