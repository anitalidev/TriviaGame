#include "optionsmenu.h"

#include <QVBoxLayout>
#include <QPushButton>

OptionsMenu::OptionsMenu(QWidget* parent) : QWidget (parent) {
    // QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);

    // layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &OptionsMenu::back);

    // setLayout(layout);
}
