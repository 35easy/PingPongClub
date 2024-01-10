// player.cpp
#include "player.h"

Player::Player(int id, const QString& name, const QString& gender)
    : id(id), name(name), gender(gender) {}

Player::Player( const QString& name, const QString& gender)
    :  name(name), gender(gender) {}


int Player::getId() const {
    return id;
}

QString Player::getName() const {
    return name;
}

QString Player::getGender() const {
    return gender;
}

void Player::setPhone(QString phone)
{
    this->phone=phone;
}
