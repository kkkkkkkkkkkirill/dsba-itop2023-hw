#include "sorter.h"

sorter::sorter(QObject *parent)
    : QObject{parent}
{

}

bool sorter::sortByNameAscending(const Game &game1, const Game &game2) {
    return game1.name < game2.name;
}

bool sorter::sortByNameDescending(const Game &game1, const Game &game2) {
    return game1.name > game2.name;
}

bool sorter::sortByRatingAscending(const Game &game1, const Game &game2) {
    return game1.rating < game2.rating;
}

bool sorter::sortByRatingDescending(const Game &game1, const Game &game2) {
    return game1.rating > game2.rating;
}

bool sorter::sortByReleaseDateAscending(const Game &game1, const Game &game2) {
    return game1.releaseDate < game2.releaseDate;
}

bool sorter::sortByReleaseDateDescending(const Game &game1, const Game &game2) {
    return game1.releaseDate > game2.releaseDate;
}
