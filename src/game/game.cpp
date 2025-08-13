#include "game.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>
#include "questionbank.h"

Game::Game(QWidget* parent) : QWidget(parent) {
    QGridLayout* grid = new QGridLayout(this);

    QPushButton* quitBtn = new QPushButton("Quit", this);
    quitBtn->setFixedSize(80, 30);
    grid->addWidget(quitBtn, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    connect(quitBtn, &QPushButton::clicked, this, &Game::quit);

    prompt_ = new QLabel(this);
    prompt_->setWordWrap(true);

    answer_ = new QLineEdit(this);
    answer_->setFixedHeight(40);

    submit_ = new QPushButton("Submit", this);
    submit_->setFixedHeight(80);

    QVBoxLayout* input = new QVBoxLayout;
    input->setSpacing(2);
    input->setContentsMargins(0, 0, 0, 0);
    input->addWidget(prompt_);
    input->addWidget(answer_);
    input->addWidget(submit_);

    grid->addLayout(input, 1, 0, 1, -1, Qt::AlignTop);
    grid->setVerticalSpacing(2);

    prompt_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    answer_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    submit_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    answer_->setClearButtonEnabled(true);

    connect(answer_, &QLineEdit::returnPressed, submit_, &QPushButton::click);
    connect(submit_, &QPushButton::clicked, this, &Game::onSubmit);

    setLayout(grid);
}

void Game::start() {
    lives_ = g_settings.lives;
    bank_ = g_settings.questions;

    startRun();
}

void Game::startRun() {
    if (!bank_ || bank_->isEmpty() || bank_->questionsComplete()) {
        QMessageBox::information(this, "Done", "No questions available.");
        emit exitToMenu();
        return;
    }

    currQ_ = bank_->nextQuestion();
    if (!currQ_) {
        QMessageBox::information(this, "Done", "You finished all questions!");
        emit exitToMenu();
        return;
    }

    prompt_->setText(currQ_->getQuestion());
    answer_->clear();
    answer_->setFocus();
    submit_->setEnabled(true);
}

void Game::onSubmit() {
    submit_->setEnabled(false);
    const QString user = answer_->text().trimmed();

    const bool correct = currQ_->checkAnswer(user);
    if (correct) {
        QMessageBox::information(this, "Correct", "Correct!");
    } else {
        if (--lives_ <= 0) {
            QMessageBox::information(this, "Game Over", "You ran out of lives :C");
            emit exitToMenu();
            return;
        }
        QMessageBox::warning(this, "Incorrect",
                             QString("Incorrect! Try again, Lives left: %1").arg(lives_));
    }

    QTimer::singleShot(0, this, &Game::startRun);
}
