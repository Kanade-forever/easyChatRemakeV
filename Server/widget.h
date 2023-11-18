#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <tcpserver.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onTcpServerStatusUpdate(QString status);
    void ontcpServerReceiveMessage(Message &message);

private slots:
    void on_btnSend_clicked();

    void on_btnImage_clicked();

private:
    Ui::Widget *ui;
    tcpserver server;

    void messageShow(Message &message);
};
#endif // WIDGET_H
