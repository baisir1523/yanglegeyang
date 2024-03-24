
#ifndef CARD_H
#define CARD_H
#include <QPushButton> //按钮类
#include <QObject>
#include <QString>  //字符串

//卡牌继承按钮类
class Card:public QPushButton

{
    Q_OBJECT       //声明这个来人card可以支持信号/槽机制
public:
    Card(QString name = nullptr);
    //name 属性是一个字符串类型，可以通过构造函数 Card(QString name = nullptr) 或直接访问 name 成员变量来设置和获取它的值。

    QString name;  //
    bool isInSlot;  //卡牌是否在卡槽内
    int clickNum;   //在卡槽被点击的次数
};

#endif // CARD_H
