#include "game.h"

#include <QVBoxLayout>
#include <QPushButton>

Game::Game(QWidget* parent) : QWidget(parent) {

    // QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);

    connect(backButton, &QPushButton::clicked, this, &Game::back);

    // setLayout(layout);
}
