#include "mainmenu.h"

#include <QPushButton>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch(1);
    layout->setSpacing(15);

    QPushButton* startButton = new QPushButton("Start Game", this);
    QPushButton* optionsButton = new QPushButton("Options", this);

    startButton->setFixedHeight(60);
    optionsButton->setFixedHeight(60);

    layout->addWidget(startButton);
    layout->addWidget(optionsButton);

    layout->addStretch(1);

    connect(startButton, &QPushButton::clicked, this, &MainMenu::start);
    connect(optionsButton, &QPushButton::clicked, this, &MainMenu::options);

    setLayout(layout);
}
