#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H
#include <QDialog>
#include "games.h"

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);
    ~FilterDialog();
    void checkInputAndAccept();
    Game getGame() const;

private:
    Ui::FilterDialog *ui;
};
#endif // FILTERDIALOG_H
