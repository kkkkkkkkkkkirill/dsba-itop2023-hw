#include "filterdialog.h"
#include "ui_filterdialog.h"
#include "mainwindow.h"
#include <QMessageBox>

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
    connect(ui->addGameButton, &QPushButton::clicked, this, &FilterDialog::checkInputAndAccept);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

//check if the line edits aren't empty
void FilterDialog::checkInputAndAccept()
{
    if(ui->nameLineEdit->text().isEmpty() ||
        ui->ratingSpinBox->value() == 0 ||
        ui->genresLineEdit->text().isEmpty() ||
        ui->tagsLineEdit->text().isEmpty() ||
        ui->categoriesLineEdit->text().isEmpty() ||
        ui->languagesLineEdit->text().isEmpty() ||
        ui->developerLineEdit->text().isEmpty() ||
        ui->publisherLineEdit->text().isEmpty() ||
        ui->platformsLineEdit->text().isEmpty() ||
        ui->shortDescriptionLineEdit->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Fill all the gaps!");
    }
    else
    {
        accept();
    }
}

Game FilterDialog::getGame() const
{
    Game game;
    // Getting the data from the line edits
    game.name = ui->nameLineEdit->text();
    game.rating = ui->ratingSpinBox->value();
    game.genre = ui->genresLineEdit->text().split(",");
    game.tags = ui->tagsLineEdit->text().split(",");
    game.categories = ui->categoriesLineEdit->text().split(",");
    game.languages = ui->languagesLineEdit->text().split(",");
    game.developer = ui->developerLineEdit->text();
    game.publisher = ui->publisherLineEdit->text();
    game.platforms = ui->platformsLineEdit->text().split(",");
    game.shortDescription = ui->shortDescriptionLineEdit->text();
    return game;
}
