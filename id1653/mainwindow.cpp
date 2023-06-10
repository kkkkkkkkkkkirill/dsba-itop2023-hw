#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sorter.h"
#include "gamedescriptiondialog.h"
#include "dialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadGamesFromCSV();
    updateTableView();
    filterDialog = new FilterDialog(this); // initializing the FilterDialog
    gameDialog = new gameDescriptionDialog(this);  // initializing the GameDescriptionDialog
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sortComboBox_currentIndexChanged(int)));
    connect(ui->searchBar, SIGNAL(textChanged(const QString &)), this, SLOT(on_searchBar_textChanged(const QString &)));
    connect(ui->filterButton, &QPushButton::clicked, filterDialog, &QDialog::open); // opening the FilterDialog when the filter button is clicked
    connect(filterDialog, &QDialog::accepted, [this]() { // when the FilterDialog is accepted
        Game newGame = filterDialog->getGame(); // getting the game from the dialog
        addGame(newGame); //adding the game
    });
    connect(ui->gameTableWidget, &QTableWidget::doubleClicked, this, &MainWindow::on_gameTableWidget_doubleClicked); //double clicking for full description of the game
    connect(gameDialog, &gameDescriptionDialog::gameUpdated, this, &MainWindow::updateGame); // to save info about the game after editing
    connect(gameDialog, &gameDescriptionDialog::gameDeleted, this, &MainWindow::deleteGame); // delete button functionality
    connect(ui->infoButton, &QPushButton::clicked, this, &MainWindow::on_infoButton_clicked); // dialog window with description and logo
}

MainWindow::~MainWindow()
{
    delete ui;
}

//reading and getting data from csv
void MainWindow::loadGamesFromCSV()
{
    QFile inputFile("/Users/kirushaaaa_budyak/Desktop/steam_games.csv");
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to open file for reading");
        return;
    }
    QTextStream stream(&inputFile);

    // skip the header line
    stream.readLine();

    ui->gameTableWidget->setColumnCount(2);
    ui -> gameTableWidget -> setHorizontalHeaderItem(0, new QTableWidgetItem("Game"));
    ui -> gameTableWidget -> setHorizontalHeaderItem(1, new QTableWidgetItem("Rating"));
    ui -> gameTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    games.clear();
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList fields = line.split(";");

        // check for sufficient number of fields
        if(fields.size() < 22)
        {
            qWarning() << "Row does not have enough columns:" << line;
            continue;
        }

        Game game;
        game.id = fields[0];
        game.name = fields[1];
        game.shortDescription = fields[2];
        game.developer = fields[3];
        game.publisher = fields[4];
        game.type = fields[7];
        game.owners = fields[9];
        game.price = fields[12].toDouble();
        game.initialPrice = fields[13].toDouble();
        game.discount = fields[14].toDouble();
        game.ccu = fields[15].toInt();
        game.releaseDate = QDate::fromString(fields[18], "yyyy/MM/dd");
        game.requiredAge = fields[19].toInt();
        game.website = fields[20];
        game.headerImage = fields[21];
        int positiveReviews = fields[10].toInt();
        int negativeReviews = fields[11].toInt();
        int totalReviews = positiveReviews + negativeReviews;

        // calculating rating in %
        double rating = 0.0;
        if (totalReviews != 0)
        {
            rating = (double)positiveReviews / totalReviews * 100;
        }
        game.rating = rating;

        // add to games list
        games.append(game);
        // adding data from csv in game table widget (in my case name and rating)
        ui -> gameTableWidget -> insertRow(ui -> gameTableWidget -> rowCount());
        QTableWidgetItem *nameItem = new QTableWidgetItem(game.name);
        ui -> gameTableWidget -> setItem(ui -> gameTableWidget -> rowCount() - 1, 0, nameItem);
        QString ratingText = QString::number(rating) + "% ";
        QTableWidgetItem *ratingItem = new QTableWidgetItem(ratingText);
        ui -> gameTableWidget -> setItem(ui -> gameTableWidget -> rowCount() - 1, 1, ratingItem);
    }
    inputFile.close();

    // Resize columns to fit their contents
    ui -> gameTableWidget -> resizeColumnsToContents();
}

// function that updates table after sorting games by chosen parametrs from spin box
void MainWindow::updateTableView()
{
    // Clearing the table
    ui->gameTableWidget->setRowCount(0);

    // Re-adding the items from the games list
    for (const Game &game : games)
    {
        int row = ui->gameTableWidget->rowCount();
        ui->gameTableWidget->insertRow(row);

        QTableWidgetItem *nameItem = new QTableWidgetItem(game.name);
        ui->gameTableWidget->setItem(row, 0, nameItem);

        // rating
        QTableWidgetItem *ratingItem = new QTableWidgetItem(QString::number(game.rating) + "%");
        ui->gameTableWidget->setItem(row, 1, ratingItem);
        // release date
        QTableWidgetItem *releaseDateItem = new QTableWidgetItem(game.releaseDate.toString());
        ui->gameTableWidget->setItem(row, 2, releaseDateItem);
    }
}

// function that realizes search bar functionality(text line edit)
void MainWindow::on_searchBar_textChanged(const QString &text)
{
    // Clear the table
    ui->gameTableWidget->setRowCount(0);

    // Loop through games
    for (const Game &game : games)
    {
        // If the game name contains the search text, add it to the table
        if (game.name.contains(text, Qt::CaseInsensitive))
        {
            int row = ui->gameTableWidget->rowCount();
            ui->gameTableWidget->insertRow(row);

            QTableWidgetItem *nameItem = new QTableWidgetItem(game.name);
            ui->gameTableWidget->setItem(row, 0, nameItem);
        }
    }
}

// sortion algorithm
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0: // Sort by name ascending
        std::sort(games.begin(), games.end(), sorter::sortByRatingDescending);
        break;
    case 1: // Sort by name descending
        std::sort(games.begin(), games.end(), sorter::sortByRatingAscending);
        break;
    case 2: // Sort by rating ascending
        std::sort(games.begin(), games.end(), sorter::sortByReleaseDateDescending);
        break;
    case 3: // Sort by rating descending
        std::sort(games.begin(), games.end(), sorter::sortByReleaseDateAscending);
        break;
    case 4: // Sort by release date ascending
        std::sort(games.begin(), games.end(), sorter::sortByNameDescending);
        break;
    case 5: // Sort by release date descending
        std::sort(games.begin(), games.end(), sorter::sortByNameAscending);
        break;
    }
    updateTableView();
}

// adding game(in dialog window after clicking filter button)
void MainWindow::addGame(const Game& game)
{
    games.append(game);

    // Inserting a new row in the table widget
    int row = ui->gameTableWidget->rowCount();
    ui->gameTableWidget->insertRow(row);

    // Setting the game properties in the respective columns
    QTableWidgetItem *nameItem = new QTableWidgetItem(game.name);
    ui->gameTableWidget->setItem(row, 0, nameItem);

    QString ratingText = QString::number(game.rating) + "%";
    QTableWidgetItem *ratingItem = new QTableWidgetItem(ratingText);
    ui->gameTableWidget->setItem(row, 1, ratingItem);

    // updating the table view
    updateTableView();
}

void MainWindow::on_gameTableWidget_doubleClicked(const QModelIndex &index)
{
    Game game = games.at(index.row());
    gameDialog->setGame(game);
    gameDialog->show();
}


void MainWindow::updateTableRow(int row, const Game &game)
{
    // get the item for each column in the row and update its text
    // this assumes the first column is the game name, and the second column is the game rating
    // update these to match my actual table data after editing it
    auto *nameItem = ui->gameTableWidget->item(row, 0);
    if (nameItem)
    {
        nameItem->setText(game.name);
    }

    auto *ratingItem = ui->gameTableWidget->item(row, 1);
    if (ratingItem)
    {
        ratingItem->setText(QString::number(game.rating));
    }
}

//updating the info game in table after editing it
void MainWindow::updateGame(Game game)
{
    // Finding the game in the games list
    int index = -1;
    for (int i = 0; i < games.size(); ++i)
    {
        if (games[i].name == game.name
            && games[i].rating == game.rating)
        {
            index = i;
            break;
        }
    }
    // If the game was found in the list, updating it
    if (index != -1)
    {
        games[index] = game;
        updateTableRow(index, game);
    }
}

void MainWindow::deleteGame(Game game)
{
    // Find the game in the games list
    int index = -1;
    for (int i = 0; i < games.size(); ++i)
    {
        if (games[i].name == game.name
            && games[i].rating == game.rating)
        {
            index = i;
            break;
        }
    }

    // If the game was found in the list, deleting it
    if (index != -1)
    {
        games.removeAt(index);
        ui->gameTableWidget->removeRow(index);
    }
}

//showing the dialog window after clicking on info button
void MainWindow::on_infoButton_clicked()
{
    Dialog* dialog = new Dialog(this);
    dialog->show();
}
