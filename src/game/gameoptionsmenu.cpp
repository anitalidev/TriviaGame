#include "gameoptionsmenu.h"

#include <QGridLayout>
#include <QPushButton>

GameOptionsMenu::GameOptionsMenu(QWidget* parent) : QWidget(parent) {

    QGridLayout* layout = new QGridLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);
    QPushButton* startButton = new QPushButton("Start Game", this);


    backButton->setFixedSize(80, 30);

    startButton->setFixedHeight(80);
    startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(backButton, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(startButton, 1, 0, 1, -1, Qt::AlignTop);

    connect(backButton, &QPushButton::clicked, this, &GameOptionsMenu::back);
    connect(startButton, &QPushButton::clicked, this, [this]{
        g_settings.lives = 3;
        g_settings.shuffle = true;
        g_settings.playerName = "You";
        emit startRequested();
    });

    setLayout(layout);

}
