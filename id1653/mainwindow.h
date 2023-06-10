#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "games.h"
#include "filterdialog.h"
#include "gameDescriptionDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTableView();
    void loadGamesFromCSV();
    void addGame(const Game &game);
    void on_comboBox_currentIndexChanged(int index);
    void on_searchBar_textChanged(const QString &text);
    void on_gameTableWidget_doubleClicked(const QModelIndex &index);
    void updateTableRow(int row, const Game &game);
    void updateGame(Game game);
    void deleteGame(Game game);
    void on_infoButton_clicked();

private:
    Ui::MainWindow *ui;
    FilterDialog *filterDialog;
    gameDescriptionDialog *gameDialog;
    QList<Game> games; // This list holds my game data
};
#endif // MAINWINDOW_H
