#ifndef IPINPUT_H
#define IPINPUT_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QRegExpValidator>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>

class IpAddressInputWindow : public QWidget {
    Q_OBJECT
public:
    IpAddressInputWindow(QWidget *parent = nullptr);
    QString getIp();

private slots:
    void onButtonClicked();
//    void onTextChanged(const QString &text);
signals:
    void ipInputClosed();
private:
    QLineEdit *lineEdit;
    QString ip;
};

#endif // IPINPUT_H
