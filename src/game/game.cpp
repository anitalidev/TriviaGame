#include "game.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QTimer>

#include "tfquestion.h"
#include "mcquestion.h"

Game::Game(QWidget* parent) : QWidget(parent) {
    auto* grid = new QGridLayout(this);

    auto* quitBtn = new QPushButton("Quit", this);
    quitBtn->setFixedSize(80, 30);
    grid->addWidget(quitBtn, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    connect(quitBtn, &QPushButton::clicked, this, &Game::quit);

    prompt_ = new QLabel(this);
    prompt_->setWordWrap(true);

    answer_ = new QVBoxLayout;
    submit_ = new QPushButton("Submit", this);
    submit_->setFixedHeight(80);

    auto* input = new QVBoxLayout;
    input->setSpacing(2);
    input->setContentsMargins(0, 0, 0, 0);
    input->addWidget(prompt_);
    input->addLayout(answer_);
    input->addWidget(submit_);

    grid->addLayout(input, 1, 0, 1, -1, Qt::AlignTop);
    grid->setVerticalSpacing(2);

    prompt_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    submit_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setLayout(grid);
}

void Game::start() {
    lives_   = g_settings.lives;
    bank_    = g_settings.questions;

    shuffle_ = g_settings.shuffle;

    bank_->setUp(shuffle_);
    startRun();
}

void Game::startRun() {
    if (!bank_ || bank_->isEmpty() || bank_->questionsComplete()) {
        clearLayout(answer_);
        QMessageBox::information(this, "Done", "You finished all questions!");
        emit exitToMenu();
        return;
    }

    currQ_ = bank_->nextQuestion();

    prompt_->setText(currQ_->getQuestion());
    clearLayout(answer_);
    submit_->setEnabled(true);

    disconnect(submit_, nullptr, this, nullptr);

    if (auto* tfQ = dynamic_cast<TFQuestion*>(currQ_)) {
        QButtonGroup* group = new QButtonGroup(this);

        QRadioButton* trueButton = new QRadioButton("True", this);
        QRadioButton* falseButton = new QRadioButton("False", this);
        group->addButton(trueButton, 0);
        group->addButton(falseButton, 1);

        answer_->addWidget(trueButton);
        answer_->addWidget(falseButton);

        connect(submit_, &QPushButton::clicked, this, [this, group]{
            if (auto* btn = group->checkedButton())
                onSubmit(btn->text());
            else
                submit_->setEnabled(true);
        });

    } else if (auto* mcQ = dynamic_cast<MCQuestion*>(currQ_)) {
        QButtonGroup* group = new QButtonGroup(this);
        group->setExclusive(true);

        const QStringList opts = mcQ->getChoices();
        for (int i = 0; i < opts.size(); ++i) {
            QRadioButton* rb = new QRadioButton(opts[i], this);

            group->addButton(rb, i);
            answer_->addWidget(rb);
        }

        connect(submit_, &QPushButton::clicked, this, [this, group] {
            if (auto* btn = group->checkedButton())
                onSubmit(btn->text());
            else
                submit_->setEnabled(true);
        });
    } else {
        QLineEdit* input = new QLineEdit(this);
        input->setFixedHeight(40);
        answer_->addWidget(input);

        connect(input, &QLineEdit::returnPressed, submit_, &QPushButton::click);

        connect(submit_, &QPushButton::clicked, this, [this, input]{
            onSubmit(input->text());
        });
    }
}

void Game::clearLayout(QLayout* layout) {
    if (!layout) return;

    QLayoutItem* item;

    while ((item = layout->takeAt(0)) != nullptr) {
        if (auto* w = item->widget()) {
            delete w;
        } else if (auto* sub = item->layout()) {
            clearLayout(sub);
            delete sub;
        }

        delete item;
    }
}

void Game::onSubmit(const QString& text) {
    submit_->setEnabled(false);

    const bool correct = currQ_->checkAnswer(text.trimmed());
    if (correct) {
        QMessageBox::information(this, "Correct", "Correct!");
    } else {
        if (--lives_ <= 0) {
            QMessageBox::information(this, "Game Over", "You ran out of lives :C");
            emit exitToMenu();
            return;
        }
        QMessageBox::warning(this, "Incorrect", QString("Incorrect! Try again, Lives left: %1").arg(lives_));
    }
    QTimer::singleShot(0, this, &Game::startRun);
}
