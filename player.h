// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
public:
    Player(int id, const QString& name, const QString& gender);
    Player(const QString &name, const QString &gender);

    int getId() const;
    QString getName() const;
    QString getGender() const;
    void setPhone(QString phone);

private:
    int id;
    QString name;
    QString gender; // 修改为 QString 类型
    QString phone;
};

#endif // PLAYER_H
