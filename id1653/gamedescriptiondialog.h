#ifndef GAMEDESCRIPTIONDIALOG_H
#define GAMEDESCRIPTIONDIALOG_H

#include <QDialog>
#include "games.h"

namespace Ui {
class gameDescriptionDialog;
}

class gameDescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gameDescriptionDialog(QWidget *parent = nullptr);
    ~gameDescriptionDialog();

    void setGame(const Game &game);

private slots:
    void on_editButton_clicked();
    void on_deleteButton_clicked();

signals:
    void gameUpdated(const Game &game);
    void gameDeleted(Game game);

private:
    Ui::gameDescriptionDialog *ui;
    Game currentGame;  // holds the current game that is being displayed
    bool isEditMode;
};

#endif // GAMEDESCRIPTIONDIALOG_H
