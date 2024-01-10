
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QString>
#include <QDate>

class Tournament {
public:
    Tournament(int id, const QString& name, const QDate& date);

    int getId() const;
    QString getName() const;
    QDate getDate() const;

private:
    int id;
    QString name;
    QDate date;
};

#endif // TOURNAMENT_H
