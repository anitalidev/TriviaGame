#include "gameoptionsmenu.h"

#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QCheckBox>

GameOptionsMenu::GameOptionsMenu(QWidget* parent) : QWidget(parent) {
    int pastRow = 0;

    QGridLayout* layout = new QGridLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);
    QPushButton* startButton = new QPushButton("Start Game", this);


    backButton->setFixedSize(80, 30);

    startButton->setFixedHeight(80);
    startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(backButton, pastRow++, 0, Qt::AlignLeft | Qt::AlignTop);

    // Shuffle
    QLabel* shuffle = new QLabel("Randomize Order of Questions?");
    QCheckBox* askShuffle = new QCheckBox("Yes", this);

    layout->addWidget(shuffle, pastRow++, 0, 1, -1, Qt::AlignTop);
    layout->addWidget(askShuffle, pastRow++, 0, 1, -1, Qt::AlignTop);

    connect(backButton, &QPushButton::clicked, this, &GameOptionsMenu::back);

    // Difficulty
    QLabel* difficulty = new QLabel("Which difficulty would you like");
    QButtonGroup* group = new QButtonGroup(this);
    group->setExclusive(true); // Apparently optional

    QRadioButton* easyButton = new QRadioButton("Easy (5 lives)", this);
    QRadioButton* medButton = new QRadioButton("Medium (3 lives)", this);
    medButton->setChecked(true); // default medium
    QRadioButton* hardButton = new QRadioButton("Hard (1 live)", this);
    group->addButton(easyButton, 0);
    group->addButton(medButton, 1);
    group->addButton(hardButton, 2);

    layout->addWidget(difficulty, pastRow++, 0, 1, -1, Qt::AlignTop);
    layout->addWidget(easyButton, pastRow++, 0, 1, -1, Qt::AlignTop);
    layout->addWidget(medButton, pastRow++, 0, 1, -1, Qt::AlignTop);
    layout->addWidget(hardButton, pastRow++, 0, 1, -1, Qt::AlignTop);

    // Start

    layout->addWidget(startButton, pastRow++, 0, 1, -1, Qt::AlignTop);

    connect(startButton, &QPushButton::clicked, this, [this, group, askShuffle]{
        QString btn = group->checkedButton()->text();
        if (btn == "Easy (5 lives)") {
            g_settings.lives = 5;
        } else if (btn == "Medium (3 lives)") {
            g_settings.lives = 3;
        } else {
            g_settings.lives = 1;
        }
        g_settings.shuffle = askShuffle->isChecked();
        g_settings.playerName = "You";
        emit startRequested();
    });

    setLayout(layout);
}
