#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include "pass.h"

namespace Ui {
class setting;
}


class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();

private:
    Ui::setting *ui;
    setting *new_setting;
signals:
    void back(void);

};

#endif // SETTING_H
