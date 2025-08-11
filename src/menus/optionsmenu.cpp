#include "optionsmenu.h"
#include <QGridLayout>
#include <QPushButton>

OptionsMenu::OptionsMenu(QWidget* parent) : QWidget(parent) {
    QGridLayout* layout = new QGridLayout;

    QPushButton* backButton = new QPushButton("Back", this);
    QPushButton* manageButton = new QPushButton("Manage Questions", this);

    // Back button stays fixed
    backButton->setFixedSize(80, 30);

    // Manage button stretches in width but has fixed height
    manageButton->setFixedHeight(80);
    manageButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Back button: row 0, col 0
    layout->addWidget(backButton, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    // Manage button: row 1, spans all columns
    layout->addWidget(manageButton, 1, 0, 1, -1, Qt::AlignTop);

    connect(backButton, &QPushButton::clicked, this, &OptionsMenu::back);
    connect(manageButton, &QPushButton::clicked, this, &OptionsMenu::manageQuestions);

    setLayout(layout);
}
