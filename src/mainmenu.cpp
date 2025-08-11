#include "mainmenu.h"

#include <QPushButton>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* startButton = new QPushButton("Start Game", this);
    QPushButton* optionsButton = new QPushButton("Options", this);

    layout->addWidget(startButton);
    layout->addWidget(optionsButton);

    connect(startButton, &QPushButton::clicked, this, &MainMenu::start);
    connect(optionsButton, &QPushButton::clicked, this, &MainMenu::options);

    setLayout(layout);
}
