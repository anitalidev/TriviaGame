#include "managequestionsmenu.h"

#include <QVBoxLayout>
#include <QPushButton>

ManageQuestionsMenu::ManageQuestionsMenu(QWidget* parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch(1);
    layout->setSpacing(15);

    QPushButton* homeButton = new QPushButton("Home", this);
    QPushButton* addQuestoinButton = new QPushButton("Add Question", this);

    homeButton->setFixedHeight(80);
    addQuestoinButton->setFixedHeight(80);

    layout->addWidget(homeButton);
    layout->addWidget(addQuestoinButton);

    layout->addStretch(1);

    connect(homeButton, &QPushButton::clicked, this, &ManageQuestionsMenu::back);
    connect(addQuestoinButton, &QPushButton::clicked, this, &ManageQuestionsMenu::addQuestion);

    setLayout(layout);
}
