#include "setting.h"
#include "ui_setting.h"
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QWidget>
setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//禁止用户自己改变窗口尺寸

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//设置无边框
    //this->setStyleSheet("background-color: transparent;");
    this->resize(200,350);//设计窗口尺寸
    this->move(100,100);
    //*****主页面背景图片*****
    QPixmap bjt (":/image/szxx");//加载图片
    QPalette bj;
    QPixmap bjtp = bjt.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片自适应
    bj.setBrush(QPalette::Window,QBrush(bjtp));//调色板设置样式
    this->setPalette(bj);//设置背景图片
    //******窗口居中显示*******
    //获取设备屏幕大小
        QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    //获取设备像素比
    int x = (screenRect.width() - this->width()) / 2;
    int y = (screenRect.height() - this->height()) / 2;
    this->move(x,y);
    //******窗口居中显示*******

    //******设置右上角关闭按钮*******
    QPushButton *xx = new QPushButton(this);
    xx->resize(30,30);
    xx->move(170,0);
    QString styleSheet = "QPushButton { border-image: url(:/image/x); display: flex; width: 30px;height: 30px;}";
    xx->setStyleSheet(styleSheet);
    xx->show();

    connect(xx,&QPushButton::clicked,this,[=](){
        this->close();
    });

    //******设置右上角关闭按钮*******



}

setting::~setting()
{
    delete ui;
}
