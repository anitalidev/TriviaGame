#ifndef GAMEOPTIONSMENU_H
#define GAMEOPTIONSMENU_H

#include <QWidget>
#include "gamesettings.h"

class GameOptionsMenu : public QWidget
{

    Q_OBJECT

public:
    explicit GameOptionsMenu(QWidget* parent = nullptr);

signals:
    void back();
    void startRequested();
};

#endif // GAMEOPTIONSMENU_H
