
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Main_Window; }
QT_END_NAMESPACE

class Main_Window : public QWidget

{
    Q_OBJECT

public:
    Main_Window(QWidget *parent = nullptr);
    ~Main_Window();

private:
    Ui::Main_Window *ui;
};

#endif // MAIN_WINDOW_H
