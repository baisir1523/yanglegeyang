
#include "card.h"
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QDebug>

Card::Card(QString name)
{
    //加载图片
    QPixmap pix;
    //name中存储图片的名字，这里使用arg来获取name中的值，然后覆盖到%1上
    //通过bool值res来判断图片是否加载成功
    bool res = pix.load(QString(":/image/%1").arg(name));

    if(!res){
        qDebug()<<"图片加载失败";
        return;
    }

    this->name = name; //设置卡牌的属性为刚才的图片名字，这个项目中图片名代表种类名
    this->isInSlot = false;//设置卡牌的状态为未入槽
    this->clickNum = 0;//设置卡牌被点击的次数

    //一下代码是设置卡牌的图片，大小
    this->setFixedSize(50,50);
    this->setIcon(pix);
    this->setIconSize(QSize(50,50));//设置图片的大小

}

