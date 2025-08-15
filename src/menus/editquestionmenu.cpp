
#include "editquestionmenu.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>


EditQuestionMenu::EditQuestionMenu(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QFormLayout* formLayout = new QFormLayout;

    typeBox = new QComboBox(this);
    typeBox->addItems({"Multiple Choice", "True/False", "Short Answer"});

    questionEdit = new QLineEdit(this);
    answerEdit = new QLineEdit(this);

    formLayout->addRow("Type:", typeBox);
    formLayout->addRow("Question:", questionEdit);
    formLayout->addRow("Answer:", answerEdit);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    QPushButton* backButton = new QPushButton("Back", this);
    QPushButton* submitButton = new QPushButton("Submit", this);

    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(submitButton);

    mainLayout->addLayout(buttonLayout);

    connect(backButton, &QPushButton::clicked, this, &EditQuestionMenu::back);
    connect(submitButton, &QPushButton::clicked, [this]() {
        emit back();
    });

    setLayout(mainLayout);
}
