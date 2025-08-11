#ifndef GAME_H
#define GAME_H

#include <QWidget>

class Game : public QWidget
{

    Q_OBJECT

public:
    explicit Game(QWidget* parent = nullptr);

signals:
    void back();
};

#endif // GAME_H
