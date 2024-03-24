#ifndef PASS_H
#define PASS_H

#include <QWidget>
#include "card.h"
#include "main_window.h"

#include <QPushButton>
#include <QList>  //关键部件的包含
#include <QObject>
#include <QString> //字符串
#include <QTime>
#include <QLabel>  //标签
#include <QtGlobal>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class Pass;
}
QT_END_NAMESPACE

class Pass : public QWidget
{
    Q_OBJECT

public:
    explicit Pass(QWidget *parent = nullptr);
    ~Pass();
public:
    void SelectPass(int level);       //关卡选择，负责判断进入那一关,1 为第一关，2 为第二个
    bool IsTop(Card *card);           //判断卡牌是否可以点击
    void DissolveCards();             //消除卡牌
    int CanDisslveCards();            //可以消除
    void CardBeClicked();              //卡牌被点击
    void DeleteCard(QList<int> idxs);  // 消除dissolveCardContainer下标为i的卡片
    void ClearAll();                 //清除卡槽的所有牌
    void LevelTow();        // 第二关
    void ks();  //开始游戏
    void PaintEvent(QPaintEvent* event);//更改背景图片
    void fuhuo();  //复活或者是从槽中出三种牌
    void ReMoveCard();  //重新洗牌
    void RecallCard();  //撤回
    void IniClearAll();  //清除乱序序列中所有卡牌
    void CreateLevel_1();//创建3*3两层分布牌
    void CreateLevel_2();//第二关
    void EditCardColor();  //修改卡牌颜色
    //void Music();  //背景音乐
    //void StopMusic();  //stop背景音乐

public:
    int level;  //关卡
    int cardNum;  //初始卡牌种类的数量，比如第一关有5种卡，第二关14种
    //QString
    QList<Card*> *dissCard;   //消除卡牌的容器
    //QList<Card*> *isSelectedList;    // 高亮的卡片集合
    QList<Card*> *initCard;   //初始化卡牌容器
    const int CARD_SIZE = 50;   // 卡牌大小
    QSoundEffect* startSound;//背景音乐
    QString cardNames[14] = { //卡牌种类
            "baicai",
            "cao",
            "chazi",
            "fantuan",
            "huodui",
            "jiandao",
            "lindang",
            "luobo",
            "muzhuang",
            "naiping",
            "shoutao",
            "shuazi",
            "shuitong",
            "yvmi",
        };


private:
    Ui::Pass *ui;
    Pass *new_Pass;
};

#endif // PASS_H
