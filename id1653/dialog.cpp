#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    logo = new LogoWidget();
    ui->mainLayout->addWidget(logo);
}

Dialog::~Dialog()
{
    delete ui;
}
