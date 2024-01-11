#ifndef FIXTURE_H
#define FIXTURE_H
#include <QString>
#include <QDate>

class Fixture {
public:
    Fixture(int id, const QString& name, const QDate& date);
    Fixture(const QString& name, const QDate& date);
    int getId() const;
    QString getName() const;
    QDate getDate() const;
    void setID(int id);

private:
    int id;
    QString name;
    QDate date;
};

#endif // FIXTURE_H
