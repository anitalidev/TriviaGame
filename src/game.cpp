#include "game.h"

#include <QGridLayout>
#include <QPushButton>

Game::Game(QWidget* parent) : QWidget(parent) {

    QGridLayout* layout = new QGridLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);

    layout->addWidget(backButton, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    connect(backButton, &QPushButton::clicked, this, &Game::back);

    setLayout(layout);
}
