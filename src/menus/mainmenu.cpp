#include "mainmenu.h"

#include <QPushButton>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch(1);
    layout->setSpacing(15);

    QPushButton* startButton = new QPushButton("Play Game", this);
    QPushButton* optionsButton = new QPushButton("Options", this);

    startButton->setFixedHeight(80);
    optionsButton->setFixedHeight(80);

    layout->addWidget(startButton);
    layout->addWidget(optionsButton);

    layout->addStretch(1);

    connect(startButton, &QPushButton::clicked, this, &MainMenu::start);
    connect(optionsButton, &QPushButton::clicked, this, &MainMenu::options);

    setLayout(layout);
}
