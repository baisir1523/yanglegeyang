#include "pass.h"
#include "ui_pass.h"
#include <QMap>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include "setting.h"
//#include "main_window.h"
#include <QRandomGenerator>
#include <algorithm>
#include <QGraphicsEffect>
#include <algorithm>
#include <QApplication>
#include <QMainWindow>
//#include <QSoundEffect>//音频类

Pass::Pass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pass)
{
    ui->setupUi(this);


    //*******窗口设置*******
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//禁止用户自己改变窗口尺寸
    this->setWindowIcon(QIcon(":/image/icon"));
    this->setWindowTitle("羊了个羊");
    this->resize(400,730);//设计窗口尺寸
    QPixmap bjt (":/image/pass");//加载图片
    QPalette bj;
    QPixmap bjtp = bjt.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片自适应
    bj.setBrush(QPalette::Window,QBrush(bjtp));//调色板设置样式
    this->setPalette(bj);//设置背景图片
    //*******窗口设置******

    //******创建高亮，初始化，卡槽容器******

    //srand(QTime(0,0,0).secsTo(QTime::currentTime()));

    this->dissCard = new QList<Card*>();
    this->initCard = new QList<Card*>();
    //this->isSelectedList = new QList<Card*>();
    //******创建高亮，初始化，卡槽容器******

    //******设置按钮设置******
    ui->pushButton->move(20,30);
    ui->pushButton_2->move(20,30);
    QString styleSheet = "QPushButton { border-image: url(:/image/sz2); display: flex; justify-content: center; width: 201px;height: 81px;}";
    styleSheet += "QPushButton:pressed { border-image: url(:/image/sz1); display: flex; justify-content: center;width: 158px;height: 63px;}";
    ui->pushButton->setStyleSheet(styleSheet); //修改样式
    ui->pushButton_2->setStyleSheet(styleSheet); //修改样式
    //******设置按钮设置******

    //******设置按钮按下后的操作设置******
    setting *new_setting = new setting();
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        new_setting->show();
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        new_setting->show();
    });
    //******设置按钮按下设置******

    //******移出三张牌的按钮设置******
    ui->pushButton_x1->move(30,660);
    ui->pushButton_x2->move(30,660);
    QString styleSheet1 = "QPushButton { border-image: url(:/image/move_3_card1); display: flex; justify-content: center; width: 201px;height: 100px;}";
    styleSheet += "QPushButton:pressed { border-image: url(:/image/move_3_card2); display: flex; justify-content: center;max-width: 158px;max-height: 63px;}";
    ui->pushButton_x1->resize(80,80);
    ui->pushButton_x2->resize(80,80);
    ui->pushButton_x1->setStyleSheet(styleSheet1); //修改样式
    ui->pushButton_x2->setStyleSheet(styleSheet1); //修改样式
    //为按钮绑定事件
    connect(ui->pushButton_x1,&QPushButton::clicked,this,[=](){
        this->fuhuo();
    });
    connect(ui->pushButton_x2,&QPushButton::clicked,this,[=](){
        this->fuhuo();
    });
    //******移出三张牌的按钮设置******

    //******洗牌的按钮设置******
    ui->pushButton_rm1->move(300,670);
    ui->pushButton_rm2->move(300,670);
    QString styleSheet2 = "QPushButton { border-image: url(:/image/re_move_card1); display: flex; justify-content: center; width: 201px;height: 100px;}";
    styleSheet += "QPushButton:pressed { border-image: url(:/image/re_move_card1); display: flex; justify-content: center;max-width: 158px;max-height: 63px;}";
    ui->pushButton_rm1->resize(85,65);
    ui->pushButton_rm2->resize(85,65);
    ui->pushButton_rm1->setStyleSheet(styleSheet2); //修改样式
    ui->pushButton_rm2->setStyleSheet(styleSheet2); //修改样式
    //为按钮绑定事件
    connect(ui->pushButton_rm1,&QPushButton::clicked,this,[=](){
        this->ReMoveCard();
    });
    connect(ui->pushButton_rm2,&QPushButton::clicked,this,[=](){
        this->ReMoveCard();
    });
    //******洗牌的按钮设置******

    //******撤回的按钮设置******
    ui->pushButton_rom1->move(165,670);
    ui->pushButton_rom2->move(165,670);
    QString styleSheet3 = "QPushButton { border-image: url(:/image/re_move_one_card); display: flex; justify-content: center; width: 201px;height: 100px;}";
    styleSheet += "QPushButton:pressed { border-image: url(:/image/re_move_one_card); display: flex; justify-content: center;max-width: 158px;max-height: 63px;}";
    ui->pushButton_rom1->resize(85,65);
    ui->pushButton_rom2->resize(85,65);
    ui->pushButton_rom1->setStyleSheet(styleSheet3); //修改样式
    ui->pushButton_rom2->setStyleSheet(styleSheet3); //修改样式
    //为按钮绑定事件
    connect(ui->pushButton_rom1,&QPushButton::clicked,this,[=](){
        this->RecallCard();
    });
    connect(ui->pushButton_rom2,&QPushButton::clicked,this,[=](){
        this->RecallCard();
    });
    //******撤回的按钮设置******

    //******胜利页面设置******
    ui->pushButton_win->move(120,590);
    QString styleSheet4 = "QPushButton { border-image: url(:/image/returnmain); display: flex; justify-content: center; width: 201px;height: 100px;}";
    styleSheet += "QPushButton:pressed { border-image: url(:/image/returnmain); display: flex; justify-content: center;max-width: 158px;max-height: 63px;}";
    ui->pushButton_win->resize(150,60);
    ui->pushButton_win->setStyleSheet(styleSheet4); //修改样式

    //首先准备好对应的资源
    //然后新建一个图片控件
    //ui->label;
    //Label *img = new QLabel(ui->stackedWidget);
    QPixmap pix_img;
    pix_img.load(":/image/joinsleep"); //加载图片
    pix_img = pix_img.scaled(QSize(250,80));//如果显示不全，则修改图片的尺寸，
    ui->label->move(50,50);
    ui->label->setPixmap(pix_img);//通过标签显示图片
    ui->label->setGeometry(75, 50, 250, 80);//修改标签的尺寸和位置
    //this->StopMusic();
    connect(ui->pushButton_win,&QPushButton::clicked,this,[=](){
        this->close();
    });
    //******胜利页面设置******

    this->EditCardColor();
}

Pass::~Pass()
{
    ClearAll();
    delete ui;
}


void Pass::SelectPass(int level) //关卡选择
{
    if(level==1){
        this->CreateLevel_1();

    }
    else if(level==2){
        this->CreateLevel_2();//创建第二关
    }
}

bool Pass::IsTop(Card *card) //判断卡牌是否可以点击
{
    //这里定义一个临时变量cardTemp,分别传入当前控件的上 下 左 右 四个角的位置
    //childat函数判断刚才获取的位置是否有子控件对象，这里的所有子控件都是卡牌，如果检测到某个角有子控件，且这个控件
    //与被点击的card（卡牌）一致的话，则代码当前被点击的卡牌上方有卡牌覆盖，则无法点击，如果检测了四个角发现都没有则
    //可以点击，返回true
    //如果上下左右都没有，则可以点击，返回true
    //需要注意的是，childAt() 函数返回的是一个指向 QObject 的指针，因此需要使用强制类型转换将其转换为 Card 类型
    Card *cardTemp = (Card *)ui->stackedWidget->currentWidget()->childAt(card->geometry().topLeft());//左上
    if(card != cardTemp){
        return false;
    }
    cardTemp = (Card *) ui->stackedWidget->currentWidget()->childAt(card->geometry().bottomLeft());//左下
    if (card != cardTemp) {
        return false;
    }
    cardTemp = (Card *) ui->stackedWidget->currentWidget()->childAt(card->geometry().topRight());//右上
    if (card != cardTemp) {
        return false;
    }
    cardTemp = (Card *) ui->stackedWidget->currentWidget()->childAt(card->geometry().bottomRight());//右下
    if (card != cardTemp) {
        return false;
    }
    return true;

}

void Pass::DissolveCards()  //消除卡牌
{
    qDebug() << "dissolveCards";
    int scoreDelta = this->CanDisslveCards();
    if(!scoreDelta) {
        qDebug() << "不能消除";
        return;
    }
    qDebug() << "可以消除" << scoreDelta;
}

int Pass::CanDisslveCards()
{
    //先按照名称放在map中,也就是入槽
    QMap<QString,QList<int>> map;
    for(int i=0;i<dissCard->size();i++){
        map[dissCard->at(i)->name].append(i);
    }
    qDebug()<<map;
    //创建一个链表存储key
    QList<QString> keyList = map.keys();
    qDebug()<<keyList;

    //判断是否有三个一样的
    for(int i=0;i<keyList.size();i++){
        if(map[keyList[i]].size()>=3){//如果卡槽里的牌大于等于三张则判断是否有某三张是一样的
            QList<int> idxs;//用于存储要被删除的卡牌的索引
            idxs.append(map[keyList[i]].at(0));//将卡牌第一次出现的索引加入要被删除的链表中
            idxs.append(map[keyList[i]].at(1));//将卡牌第二次出现的索引加入要被删除的链表中
            idxs.append(map[keyList[i]].at(2));//将卡牌第三次出现的索引加入要被删除的链表中
            this->DeleteCard(idxs);//调用函数将idxs中的卡牌删除掉
            return 0;
        }
    }

    return 0;

}

void Pass::CardBeClicked() //卡牌被点击
{
    //被点击的卡牌
    Card *card = (Card*)sender();//将指针sender()转换为指向Card对象的指针类型，并将其赋值给card变量。

    if(!this->IsTop(card)){//先判断是否可以被点击
        qDebug()<<"不可点击";
        return;
    }

    //如何可以点击
    qDebug()<<"可以点击";
    this->initCard->removeOne(card);//在初始化容器中删除这个卡牌
    this->EditCardColor();//更改被覆盖卡的颜色

    //判断卡牌是否在槽内
    if(card->isInSlot){
        //this->ToggleHighLight(card);//给卡牌切换高亮
        return;
    }
    if(card->name == "class" /*&& this->isSelectedList->size() > 0 && this->isSelectedList->at(0)->name != "class"*/){
        delete card;//删除被点击的对象，并且释放内存
        //this->dissCard->removeOne(this->isSelectedList->at(0));//删除卡槽中第一个卡牌
        //delete this->isSelectedList->at(0);//删除最先选择的卡牌对象，并释放内存
        //this->isSelectedList->clear();//清空已经选择的卡牌容器，一般后续接着选卡牌
    }else{//如果没在卡槽内
        card->isInSlot = true;//设置卡牌在卡槽中，
        dissCard->append(card);//将卡牌加入到卡槽中
        card->move(dissCard->size() * CARD_SIZE,570); //设置卡牌在卡槽中的位置

        this->DissolveCards();
    }
    //卡牌左对齐
    for(int i=0;i<dissCard->size();i++){
        dissCard->at(i)->move(((i) * CARD_SIZE)+35,580);
    }



    //判断是否胜利
    if(this->cardNum == 0){
        qDebug()<<"胜利";
        if(this->level == 1){
            //如果是第一个则进入第二关
            this->LevelTow();

        }
        else if(this->level == 2){
            //如果是第二关则....

            ui->stackedWidget->setCurrentIndex(3);
        }
    }
    else if(this->cardNum == this->dissCard->size() || this->dissCard->size() >= 7){
        qDebug() << "没有卡片可以选择了";
        // 如果没有卡牌可以选了，但是卡槽还存在卡片, 获取卡槽的
        fuhuo();
        if(QMessageBox::Ok == QMessageBox::information(this, "提示", "游戏失败")) {

        }
    }

    this->EditCardColor();
}

void Pass::DeleteCard(QList<int> idxs)//idxs为要消除的卡牌，消除卡牌
{
    std::sort(idxs.begin(),idxs.end());//因为是通过索引进行删除的，索引要先对索引进行排序
    for(int i= idxs.size()-1;i>=0;i--){
        Card *card = dissCard->at(idxs.at(i)); //通过索引找到要删除的牌
        dissCard->removeAt(idxs.at(i)); //删除
        delete card;//释放内存
    }
    this->cardNum -=idxs.size();//刚才消掉了几个牌，那卡牌的总数量就少几个牌

}

void Pass::ClearAll()  //清除槽中所有卡牌
{
    this->cardNum -= dissCard->size(); //卡牌总数减去槽中的卡牌总数
    for(int i = dissCard->size() - 1;i>=0;i--){
        Card* card = dissCard->at(i);//指针指向要删除的地方
        dissCard ->removeAt(i);//删除指针指向的地方
        delete card;//释放指针内存
    }
}

void Pass::IniClearAll()  //清除乱序序列中所有卡牌
{
    for(int i = initCard->size() - 1;i>=0;i--){
        Card* card = initCard->at(i);//指针指向要删除的地方
        initCard ->removeAt(i);//删除指针指向的地方
        delete card;//释放指针内存
    }
}

void Pass::CreateLevel_1()
{
    static int x = 0,y = 0;
    for(int i=0 ;i<3;i++){
        for(int j=0;j<2;j++){
            int cardIdx = rand()%3;
            for(int k=0;k<3;k++){
                Card *card = new Card(this->cardNames[cardIdx]);
                initCard->append(card);//将刚刚新生成的卡牌加入到等待消除的链表中
                connect(card,&Card::clicked,this,&Pass::CardBeClicked);
                //关卡页面基于栈容器
                //将当前卡牌设置为栈容器的子对象，这样卡牌就可以显示在栈容器的上方
                //card->setParent(ui->stackedWidget->currentWidget());
            }
        }
    }

    std::shuffle(initCard->begin(), initCard->end(),0);//打乱qlist中的元素

    int count=0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 3; k++) {
                if(count < 18) {
                    Card *card = initCard->at(count++);
                    card->setParent(ui->stackedWidget->currentWidget());
                    card->move(55+x,120+y);
                    x+=50+70;
                    card->show();
                }
            }
            x=0;
            y+=30;
        }
        y+=70;
    }
    this->cardNum = initCard->size();//生成卡牌后记录刚才生成了多少卡牌
    this->EditCardColor();
    x=y=0;
}

void Pass::CreateLevel_2()
{
    for(int i=0;i<120;){
        int cardIdx = rand()%14;
        for(int k=0;k<3;k++){
            Card *card = new Card(this->cardNames[cardIdx]);
            initCard->append(card);//将刚刚新生成的卡牌加入到等待消除的链表中
            connect(card,&Card::clicked,this,&Pass::CardBeClicked);
            //关卡页面基于栈容器
            //将当前卡牌设置为栈容器的子对象，这样卡牌就可以显示在栈容器的上方
            //card->setParent(ui->stackedWidget->currentWidget());
            ++i;
        }
    }

    std::shuffle(initCard->begin(), initCard->end(),0);//打乱qlist中的元素

    static int x = 0,y = 0;
    int count=0;
    for(int i=0;i<20;i++){  //左边的一列
        if(count<120){
            Card *card = initCard->at(count++);
            card->setParent(ui->stackedWidget->currentWidget());
            card->move(50,100+y);
            y+=9;
            card->show();
        }
    }

    y=0;
    for(int i=0;i<20;i++){  //右边的一列
        if(count<120){
            Card *card = initCard->at(count++);
            card->setParent(ui->stackedWidget->currentWidget());
            card->move(305,100+y);
            y+=9;
            card->show();
        }
    }

    y=x=0;
    for(int i=0;i<5;i++){  //中间
        for(int j=0;j<4;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(100+x,120+y);
                x+=51;
                card->show();
            }
        }
        x=0;
        y+=55;
    }

    y=x=0;
    for(int i=0;i<3;i++){  //中间的中间
        for(int j=0;j<3;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(120+x,140+y);

                x+=51;
                card->show();
            }
        }
        x=0;
        y+=55;
    }

    y=x=0;
    for(int i=0;i<5;i++){  //中间的下面
        for(int j=0;j<2;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(150+x,190+y);

                x+=51;
                card->show();
            }
        }
        x=0;
        y+=55;
    }

    y=x=0;
    for(int i=0;i<2;i++){  //中间的下面的上面
        for(int j=0;j<4;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(100+x,390+y);

                x+=51;
                card->show();
            }
        }
        x=0;
        y+=55;
    }

    y=x=0;
    for(int i=0;i<2;i++){  //中间的下面的两边面
        for(int j=0;j<2;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(70+x,390+y);

                x+=200;
                card->show();
            }
        }
        x=0;
        y+=55;
    }

    y=x=0;
    for(int i=0;i<5;i++){  //中间的下面
        for(int j=0;j<4;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(100+x,320+y);
                x+=51;
                card->show();
            }
        }
        x=0;
        y+=20;
    }

    y=x=0;
    for(int i=0;i<2;i++){  //最后9张
        for(int j=0;j<2;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(40+x,430+y);
                x+=51;
                card->show();
            }
        }
        x=0;
        y+=20;
    }
    y=x=0;
    for(int i=0;i<2;i++){  //最后9张
        for(int j=0;j<2;j++){
            if(count<120){
                Card *card = initCard->at(count++);
                card->setParent(ui->stackedWidget->currentWidget());
                card->move(40+x,430+y);
                x+=265;
                card->show();
            }
        }
        x=0;
        y+=51;
    }

    Card *card = initCard->at(count++);//最后一张
    card->setParent(ui->stackedWidget->currentWidget());
    card->move(150,330);
    card->show();

    qDebug()<<count;


    this->cardNum = initCard->size();//生成卡牌后记录刚才生成了多少卡牌
    this->EditCardColor();
    x=y=0;
}

void Pass::EditCardColor() {
    for (int i = 0; i < this->initCard->size(); i++) {
        Card *card = initCard->at(i);
        if (!this->IsTop(card)) { // 如果卡牌被覆盖，则给按钮设置灰色
            card->setEnabled(false);
        }
        else{//没覆盖则设置正常
            card->setEnabled(true);
        }
    }
}

void Pass::LevelTow()//第二关
{
    this->level = 2;
    // 切换页面
    ui->stackedWidget->setCurrentIndex(2);
    // 更改第几关

    this->SelectPass(2);
}

void Pass::ks() //开始游戏
{
    this->level = 1;
    //this->Music();
    ui->stackedWidget->setCurrentIndex(1);

    this->SelectPass(1);

}

void Pass::fuhuo()//从槽里移出三张牌
{
    if(dissCard->size()>=3){
        int x = 30;
        static int y = 510;
        for(int i = 0;i < 3; i++){
            initCard->insert(0,dissCard->takeAt(0));
            initCard->at(0)->move(55+x,y);
            initCard->at(0)->isInSlot = false;
            x+=70;


        }
        y -=35;
        //QList<Card *>::Iterator iter=ini

        return;
    }
    else{
        qDebug()<<"不可复活";
        return;
    }
}

void Pass::ReMoveCard()//洗牌
{
    int x=0,y=0;

    if(level == 1){
        std::shuffle(initCard->begin(), initCard->end(),0);//先打乱qlist中的元素

        int count=0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 3; k++) {
                    if(count < 18) {
                        Card *card = initCard->at(count++);
                        card->setParent(ui->stackedWidget->currentWidget());
                        card->move(55+x,120+y);
                        x+=50+70;
                        card->show();
                    }
                }
                x=0;
                y+=30;
            }
            y+=70;
        }
        this->cardNum = initCard->size();//生成卡牌后记录刚才生成了多少卡牌
        this->EditCardColor();
        x=y=0;
    }
    else if(level == 2){
        std::shuffle(initCard->begin(), initCard->end(),0);//打乱qlist中的元素、
        for(int i = 0;i<initCard->size();i++){
            initCard->at(i)->move(50+rand()%250,50+rand()%400);
        }

    }
}

void Pass::RecallCard() //
{
    if(dissCard->size()>=1){
        int i =dissCard->size();
        static int y = 0; //不止一次撤回机会，使用静态变量保存y的值
        qDebug()<<i;
        initCard->insert(0,dissCard->takeAt(i-1)); //移出最后一个元素
        initCard->at(0)->move(200,520-y);
        y+=20;
        initCard->at(0)->isInSlot = false; //设置为为入槽状态
    }

    return;
}
















