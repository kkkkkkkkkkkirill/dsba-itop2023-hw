#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "logowidget.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    LogoWidget *logo;
};

#endif // DIALOG_H
