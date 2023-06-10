#include "gameDescriptionDialog.h"
#include "ui_gameDescriptionDialog.h"

gameDescriptionDialog::gameDescriptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameDescriptionDialog)
{
    ui->setupUi(this);
    isEditMode = false;
}

gameDescriptionDialog::~gameDescriptionDialog()
{
    delete ui;
}

void gameDescriptionDialog::setGame(const Game &game)
{
    currentGame = game;

    QString ratingCategory;
    double rating = game.rating;
    if (rating >= 95) ratingCategory = "Overwhelmingly Positive";
    else if (rating >= 94) ratingCategory = "Very Positive";
    else if (rating >= 80) ratingCategory = "Positive";
    else if (rating >= 70) ratingCategory = "Mostly Positive";
    else if (rating >= 40) ratingCategory = "Mixed";
    else if (rating >= 20) ratingCategory = "Mostly Negative";
    else if (rating >= 10) ratingCategory = "Negative";
    else if (rating >= 5) ratingCategory = "Very Negative";
    else if (rating == 0) ratingCategory = "No review";
    else ratingCategory = "Overwhelmingly Negative";

    QString ratingText = QString::number(rating) + "% - " + ratingCategory;
    ui->ratingLabel->setText(ratingText);

    ui->nameEdit->setText(game.name);
    ui->releaseDateEdit->setText(game.releaseDate.toString("dd-MM-yyyy"));
    ui->developerEdit->setText(game.developer);
    ui->publisherEdit->setText(game.publisher);
    ui->ownersEdit->setText(game.owners);
    ui->descriptionEdit->setPlainText(game.shortDescription);

    // setting the text edits to readonly view
    ui->nameEdit->setReadOnly(true);
    ui->releaseDateEdit->setReadOnly(true);
    ui->developerEdit->setReadOnly(true);
    ui->publisherEdit->setReadOnly(true);
    ui->ownersEdit->setReadOnly(true);
    ui->descriptionEdit->setReadOnly(true);
}

void gameDescriptionDialog::on_editButton_clicked()
{
    if (isEditMode)
    {
        // Changing button text back to "Edit"
        ui->editButton->setText("Edit");

        // Disable editing
        ui->nameEdit->setReadOnly(true);
        ui->developerEdit->setReadOnly(true);
        ui->publisherEdit->setReadOnly(true);
        ui->ownersEdit->setReadOnly(true);
        ui->descriptionEdit->setReadOnly(true);

        // Save changes to games
        currentGame.name = ui->nameEdit->text();
        currentGame.releaseDate = QDate::fromString(ui->releaseDateEdit->text(), "yyyy/MM/dd");
        currentGame.developer = ui->developerEdit->text();
        currentGame.publisher = ui->publisherEdit->text();
        currentGame.owners = ui->ownersEdit->text();
        currentGame.shortDescription = ui->descriptionEdit->toPlainText();

        // Emit signal to mainwindow to update the game in the list
        emit gameUpdated(currentGame);

        // Set edit mode to false
        isEditMode = false;
    }
    else
    {
        // Change button text to "Save"
        ui->editButton->setText("Save");

        // Enable editing
        ui->nameEdit->setReadOnly(false);
        ui->releaseDateEdit->setReadOnly(false);
        ui->developerEdit->setReadOnly(false);
        ui->publisherEdit->setReadOnly(false);
        ui->ownersEdit->setReadOnly(false);
        ui->descriptionEdit->setReadOnly(false);

        // Set edit mode to true
        isEditMode = true;
    }
}

void gameDescriptionDialog::on_deleteButton_clicked()
{
    emit gameDeleted(currentGame);
    this->close(); // closing the dialog
}
