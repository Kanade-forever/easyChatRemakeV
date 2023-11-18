#include "ipinput.h"

IpAddressInputWindow::IpAddressInputWindow(QWidget *parent)
{
    Q_UNUSED(parent);

    this->setWindowTitle("Connect");

    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout(this);

    lineEdit = new QLineEdit(this);
    QPushButton *button = new QPushButton("确认", this);

    QLabel * label = new QLabel("Input IP:",this);

    // 设置IP地址格式验证器
    QRegularExpression ipRegex("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(ipRegex, this);
    lineEdit->setValidator(validator);

    // 添加组件到布局
    hlayout->addWidget(label);
    hlayout->addWidget(lineEdit);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(button);


    // 连接按钮的点击信号
    connect(button, &QPushButton::clicked, this, &IpAddressInputWindow::onButtonClicked);
//    connect(this->lineEdit,&QLineEdit::textChanged,this,&IpAddressInputWindow::onTextChanged);
}

QString IpAddressInputWindow::getIp()
{
    return ip;
}

void IpAddressInputWindow::onButtonClicked()
{
    QRegularExpression ipRegex("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(ipRegex, this);
    ip = this->lineEdit->text();
    int pos = 0;
    if(validator->validate(ip,pos) != QValidator::Acceptable){
        QMessageBox::warning(this,"Warning","输入的IP格式错误!");
    }
    else{
        this->hide();
    }
}
/*
void IpAddressInputWindow::onTextChanged(const QString &text)
{
    if(text.isEmpty())return;
    int index = text.length()-1;
    if(text.at(index) == '.' || text.count('.') == 3){
        return;
    }
    switch (index) {
    case 0:return;
    case 1:{
        if(text>"25"){lineEdit->insert(".");return;}
        else return;
    }
    case 2:{
        if(text.at(index)>'5'){lineEdit->insert(".");return;}
        else return;
    }
    }
    if(text.at(index-1) == '.'){
        return;
    }
    else if(text.at(index-1)>'3'){
        lineEdit->insert(".");
        return;
    }
    else{
        if(text.at(index-1) == '2' && text.at(index)>'5'){
            lineEdit->insert(".");
            return;
        }
    }
    if(text.at(index-2) == '.'){
        lineEdit->insert(".");
        return;
    }

}*/
