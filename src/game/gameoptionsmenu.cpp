#include "gameoptionsmenu.h"

#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>

GameOptionsMenu::GameOptionsMenu(QWidget* parent) : QWidget(parent) {

    QGridLayout* layout = new QGridLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);
    QPushButton* startButton = new QPushButton("Start Game", this);


    backButton->setFixedSize(80, 30);

    startButton->setFixedHeight(80);
    startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(backButton, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    QCheckBox* askShuffle = new QCheckBox("Shuffle Questions", this);

    layout->addWidget(askShuffle, 1, 0, 1, -1, Qt::AlignTop);

    connect(backButton, &QPushButton::clicked, this, &GameOptionsMenu::back);
    connect(startButton, &QPushButton::clicked, this, [this, askShuffle]{
        g_settings.lives = 3;
        g_settings.shuffle = askShuffle->isChecked();
        g_settings.playerName = "You";
        emit startRequested();
    });

    layout->addWidget(startButton, 2, 0, 1, -1, Qt::AlignTop);

    setLayout(layout);
}
