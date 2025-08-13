#include "game.h"
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>

#include "questionbank.h"

Game::Game(QWidget* parent) : QWidget(parent) {

    QGridLayout* layout = new QGridLayout(this);

    QPushButton* quitButton = new QPushButton("Quit", this);
    quitButton->setFixedSize(80, 30);

    layout->addWidget(quitButton, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    connect(quitButton, &QPushButton::clicked, this, &Game::quit);

    setLayout(layout);
}

void Game::start() {
    lives_ = g_settings.lives;
    bank_ = std::move(g_settings.questions);

    startRun();
}

void Game::startRun() {
    if (!bank_ || bank_->isEmpty()) {
        QMessageBox::information(this, "Done", "No questions available.");
        emit exitToMenu();
        return;
    }

    if (bank_->questionsComplete()) {
        QMessageBox::information(this, "Done", "You finished all questions!");
        emit exitToMenu();
        return;
    }

    Question* q = bank_->nextQuestion();

    QGridLayout* grid = qobject_cast<QGridLayout*>(layout());
    if (!grid) return;

    for (int r = grid->rowCount() - 1; r >= 1; --r) {
        for (int c = grid->columnCount() - 1; c >= 0; --c) {

            if (QLayoutItem* item = grid->itemAtPosition(r, c)) {
                if (QWidget* w = item->widget()) {
                    grid->removeWidget(w);
                    w->deleteLater();

                } else {
                    grid->removeItem(item);
                    delete item;

                }
            }

        }
    }

    QLabel* prompt     = new QLabel(q->getQuestion(), this);
    QLineEdit* answer  = new QLineEdit(this);
    QPushButton* submit = new QPushButton("Submit", this);

    submit->setFixedHeight(80);
    answer->setFixedHeight(40);

    QVBoxLayout* input = new QVBoxLayout;
    input->setSpacing(2);
    input->addWidget(prompt);
    input->addWidget(answer);
    input->addWidget(submit);

    grid->addLayout(input, 1, 0, 1, -1, Qt::AlignTop);

    grid->setSpacing(2);

    prompt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    answer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    submit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    connect(submit, &QPushButton::clicked, this, [this, q, answer] {
        const QString user = answer->text().trimmed();

        const bool correct = q->checkAnswer(user);

        if (correct) {
            QMessageBox::information(this, "Correct", "Correct!");
        } else {
            if (--lives_ <= 0) {
                QMessageBox::information(this, "Game Over", "You ran out of lives.");
                emit exitToMenu();
                return;
            }
            QMessageBox::warning(this, "Incorrect",
                                 QString("Try the next one. Lives left: %1").arg(lives_));
        }

        startRun();
    });
}
