#include "managequestionsmenu.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>

ManageQuestionsMenu::ManageQuestionsMenu(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(12, 12, 12, 12);

    QPushButton* backButton = new QPushButton("Back", this);
    backButton->setFixedSize(80, 30);

    questionList_ = new QListWidget(this);
    layout->addWidget(backButton, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(questionList_, 1);

    QHBoxLayout* row = new QHBoxLayout();
    QPushButton* addQuestionButton = new QPushButton("Add Question", this);
    removeButton_ = new QPushButton("Remove", this);

    addQuestionButton->setFixedHeight(40);
    removeButton_->setFixedHeight(40);

    row->addStretch(1);
    row->addWidget(addQuestionButton);
    row->addWidget(removeButton_);
    row->addStretch(1);
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

void ManageQuestionsMenu::setQuestions(QuestionBank& items) {
    questionList_->clear();
    questionList_->addItems(items.toQStringList());

    removeButton_->setEnabled(!items.isEmpty());
}
