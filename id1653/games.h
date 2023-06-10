#ifndef GAMES_H
#define GAMES_H

#include <QString>
#include <QDate>

struct Game {
    QString id;
    QString name;
    QString shortDescription;
    QString developer;
    QString publisher;
    QStringList genre;
    QStringList tags;
    QString type;
    QStringList categories;
    QString owners;
    int positiveReviews;
    int negativeReviews;
    double rating;
    double price;
    double initialPrice;
    double discount;
    int ccu;
    QStringList languages;
    QStringList platforms;
    QDate releaseDate;
    QString releaseDateRange;
    int requiredAge;
    QString website;
    QString headerImage;
};

#endif // GAMES_H
