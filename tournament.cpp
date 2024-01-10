#include "tournament.h"

Tournament::Tournament(int id, const QString& name, const QDate& date)
    : id(id), name(name), date(date) {}

int Tournament::getId() const {
    return id;
}

QString Tournament::getName() const {
    return name;
}

QDate Tournament::getDate() const {
    return date;
}
