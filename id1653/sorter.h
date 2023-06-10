#ifndef SORTER_H
#define SORTER_H

#include <QObject>
#include "games.h"

class sorter : public QObject
{
    Q_OBJECT
public:
    explicit sorter(QObject *parent = nullptr);
    static bool sortByNameAscending(const Game &game1, const Game &game2);
    static bool sortByNameDescending(const Game &game1, const Game &game2);
    static bool sortByRatingAscending(const Game &game1, const Game &game2);
    static bool sortByRatingDescending(const Game &game1, const Game &game2);
    static bool sortByReleaseDateAscending(const Game &game1, const Game &game2);
    static bool sortByReleaseDateDescending(const Game &game1, const Game &game2);
signals:

};

#endif // SORTER_H
