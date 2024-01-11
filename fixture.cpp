#include "fixture.h"

Fixture::Fixture(int id, const QString& name, const QDate& date)
    : id(id), name(name), date(date) {}

Fixture::Fixture(const QString &name, const QDate &date)
 :  name(name), date(date) {}

int Fixture::getId() const {
    return id;
}

QString Fixture::getName() const {
    return name;
}

QDate Fixture::getDate() const {
    return date;
}

void Fixture::setID(int id)
{
    this->id=id;
}
