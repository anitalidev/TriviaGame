#include "game.h"
#include <QGridLayout>
#include <QPushButton>
#include "questionbank.h"

Game::Game(QWidget* parent) : QWidget(parent) {

    QGridLayout* layout = new QGridLayout(this);

    QPushButton* quitButton = new QPushButton("Quit", this);
    quitButton->setFixedSize(80, 30);

    layout->addWidget(quitButton, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    connect(quitButton, &QPushButton::clicked, this, &Game::quit);

    startRun();

    setLayout(layout);
}

void Game::startRun() {
    // TODO: pull first question, show it, wire answer input, decrement lives, etc.
    // e.g., auto* q = bank_->nextQuestion();
}
