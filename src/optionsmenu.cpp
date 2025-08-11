#include "optionsmenu.h"

#include <QGridLayout>
#include <QPushButton>

OptionsMenu::OptionsMenu(QWidget* parent) : QWidget (parent) {

    QGridLayout* layout = new QGridLayout;

    QPushButton* backButton = new QPushButton("Back", this);

    layout->addWidget(backButton, 0, 0, Qt::AlignLeft | Qt::AlignTop);

    connect(backButton, &QPushButton::clicked, this, &OptionsMenu::back);

    setLayout(layout);

}
