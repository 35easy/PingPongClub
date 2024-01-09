#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QWidget>

namespace Ui {
class Tournament;
}

class Tournament : public QWidget
{
    Q_OBJECT

public:
    explicit Tournament(QWidget *parent = nullptr);
    ~Tournament();

private:
    Ui::Tournament *ui;
};

#endif // TOURNAMENT_H
