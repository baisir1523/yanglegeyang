
#include "main_window.h"
#include "ui_main_window.h"
#include <QPushButton>
#include "pass.h"


Main_Window::Main_Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Main_Window)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//禁止用户自己改变窗口尺寸
    this->resize(400,730);//设计窗口尺寸

    //*****主页面背景图片*****
    this->setWindowIcon(QIcon(":/image/icon"));
    this->setWindowTitle("羊了个羊");
    QPixmap bjt (":/image/MainWidget");//加载图片
    QPalette bj;
    QPixmap bjtp = bjt.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片自适应
    bj.setBrush(QPalette::Window,QBrush(bjtp));//调色板设置样式
    this->setPalette(bj);//设置背景图片

    //*****更改开始游戏按钮背景样式*****
    //为按钮设置样式，类似于css，但setStyleSheet函数只能调用一次，再次调用会导致覆盖前一次的效果，所以需要一个字符串将按下和正常两种按钮情况的样式表加起来，然后再调用
    QPushButton *button = new QPushButton(this);
    button->move(96,590);
    QString styleSheet = "QPushButton { border-image: url(:/image/go_play); display: flex; justify-content: center; width: 201px;height: 81px;}";
    styleSheet += "QPushButton:pressed { border-image: url(:/image/go_play2); display: flex; justify-content: center;width: 158px;height: 63px;}";
    button->setStyleSheet(styleSheet); //修改样式

    //******检测******
    Pass *new_pass = new Pass(this);

    connect(button,&QPushButton::clicked,this,[=](){
        new_pass->show();
        //开始前预先清除乱序链表和卡槽链表
        new_pass->IniClearAll();
        new_pass->ClearAll();
        new_pass->ks();
    });

   //Pass *passPage = new Pass(this);



}

Main_Window::~Main_Window()
{
    delete ui;
}


