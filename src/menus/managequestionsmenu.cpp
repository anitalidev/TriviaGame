#include "managequestionsmenu.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>

ManageQuestionsMenu::ManageQuestionsMenu(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(12, 12, 12, 12);

    questionList_ = new QListWidget(this);
    layout->addWidget(questionList_, 1);

    QHBoxLayout* row = new QHBoxLayout();
    QPushButton* addQuestionButton = new QPushButton("Add Question", this);
    removeButton_ = new QPushButton("Remove", this);
    QPushButton* backButton = new QPushButton("Back", this);

    addQuestionButton->setFixedHeight(40);
    removeButton_->setFixedHeight(40);
    backButton->setFixedHeight(40);

    row->addWidget(backButton);
    row->addStretch(2);
    row->addWidget(addQuestionButton);
    row->addWidget(removeButton_);
    layout->addLayout(row);

    connect(backButton,        &QPushButton::clicked, this, &ManageQuestionsMenu::back);
    connect(addQuestionButton, &QPushButton::clicked, this, &ManageQuestionsMenu::addQuestion);

    connect(removeButton_, &QPushButton::clicked, this, [this]{
        const int row = questionList_->currentRow();
        if (row >= 0) {
            emit remove(row);
        }
    });
}

void ManageQuestionsMenu::setQuestions(const QStringList& items) {
    questionList_->clear();
    questionList_->addItems(items);

    removeButton_->setEnabled(!items.isEmpty());
}
