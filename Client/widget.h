#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <message.h>
#include <QInputDialog>
#include "ipinput.h"
#include "tcpsocket.h"


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
    void onSocketReceiveMessage(Message &message);

private slots:
    void on_btnSend_clicked();

    void on_btnImage_clicked();

    void on_btnDisconnect_clicked();

    void on_btnConnect_clicked();

    void onIpInputClosed();

private:
    Ui::Widget *ui;
    tcpsocket socket;

    IpAddressInputWindow *ipinput = new IpAddressInputWindow(this);

    void messageShow(Message &message);

};
#endif // WIDGET_H
