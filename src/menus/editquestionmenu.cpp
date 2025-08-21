
#include "editquestionmenu.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>

#include "addquestionmenu.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>

#include "mcquestion.h"
#include "tfquestion.h"
#include "saquestion.h"

// REQUIRES: toEdit_ must have been set to a non-nullptr
EditQuestionMenu::EditQuestionMenu(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    typeStack = new QStackedWidget(this);
    mainLayout->addWidget(typeStack);

    // Multiple Choice
    mcPage = new QWidget(this);
    {
        QLabel* mcLabel = new QLabel("Multiple Choice");

        QFormLayout* mcForm = new QFormLayout(mcPage);
        mcQuestion = new QLineEdit(mcPage);
        mcQuestion->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        mcForm->addRow("Question:", mcQuestion);

        QWidget* choicesBox = new QWidget(mcPage);
        mcChoicesLayout = new QVBoxLayout(choicesBox);
        mcChoicesLayout->setContentsMargins(0,0,0,0);
        mcChoicesLayout->setSpacing(6);

        mcCorrectGroup = new QButtonGroup(this);
        mcCorrectGroup->setExclusive(true);

        mcAddChoiceBtn = new QPushButton("Add choice", mcPage);
        connect(mcAddChoiceBtn, &QPushButton::clicked, this, [this]{
            const bool first = mcCorrectGroup->buttons().isEmpty();
            addMCChoiceRow(QString(), first);
        });

        mcForm->addRow(mcLabel);
        mcForm->addRow(new QLabel("Choices (select the correct one):", mcPage));
        mcForm->addRow(choicesBox);
        mcForm->addRow("", mcAddChoiceBtn);

        if (auto* first = mcCorrectGroup->button(0)) first->setChecked(true);

        mcForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    }
    typeStack->addWidget(mcPage); // 0

    // True/False
    tfPage = new QWidget(this);
    {
        QLabel* tfLabel = new QLabel("True/False");

        QFormLayout* tfForm = new QFormLayout(tfPage);
        tfQuestion = new QLineEdit(tfPage);
        tfQuestion->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        tfAnswer   = new QComboBox(tfPage);
        tfAnswer->addItems({"True", "False"});

        tfForm->addRow(tfLabel);
        tfForm->addRow("Question:", tfQuestion);
        tfForm->addRow("Answer:",   tfAnswer);

        tfForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    }
    typeStack->addWidget(tfPage); // 1

    // Short Answer
    saPage = new QWidget(this);
    {
        QLabel* saLabel = new QLabel("Short Answer");

        QFormLayout* saForm = new QFormLayout(saPage);
        saQuestion = new QLineEdit(saPage);
        saQuestion->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        saAnswer   = new QLineEdit(saPage);
        saAnswer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        saForm->addRow(saLabel);
        saForm->addRow("Question:", saQuestion);
        saForm->addRow("Answer:",   saAnswer);

        saForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    }
    typeStack->addWidget(saPage); // 2


    QHBoxLayout* buttons = new QHBoxLayout;
    backButton   = new QPushButton("Back", this);
    submitButton = new QPushButton("Submit", this);
    buttons->addWidget(backButton);
    buttons->addStretch();
    buttons->addWidget(submitButton);
    mainLayout->addLayout(buttons);

    connect(backButton, &QPushButton::clicked, this, &EditQuestionMenu::back);
    connect(submitButton, &QPushButton::clicked, this, &EditQuestionMenu::back); // TODO
}

void EditQuestionMenu::addMCChoiceRow(const QString& text, bool checked) {
    QWidget* row = new QWidget(mcPage);
    QHBoxLayout* h = new QHBoxLayout(row);
    h->setContentsMargins(0,0,0,0);
    h->setSpacing(8);

    QRadioButton* rb = new QRadioButton(row);
    const int id = mcCorrectGroup->buttons().size();
    mcCorrectGroup->addButton(rb, id);
    rb->setChecked(checked);

    QLineEdit* edit = new QLineEdit(row);
    edit->setPlaceholderText(QString("Choice %1").arg(id + 1));
    edit->setText(text);

    h->addWidget(rb);
    h->addWidget(edit);

    mcChoicesLayout->addWidget(row);
}

void EditQuestionMenu::submitCurrent() {
    switch (typeBox->currentIndex()) {
    case 0: { // Multiple Choice
        const QString question = mcQuestion->text().trimmed();
        if (question.isEmpty()) return;

        QStringList choices;
        choices.reserve(mcChoicesLayout->count());

        for (int i = 0; i < mcChoicesLayout->count(); ++i) {
            if (auto* rowItem = mcChoicesLayout->itemAt(i)) {
                if (auto* row = rowItem->widget()) {
                    if (auto* rowLayout = qobject_cast<QHBoxLayout*>(row->layout())) {
                        if (auto* edit = qobject_cast<QLineEdit*>(rowLayout->itemAt(1)->widget())) {
                            choices << edit->text().trimmed();
                        }
                    }
                }
            }
        }

        int nonEmpty = 0;
        for (const auto& c : choices) {
            if (!c.isEmpty()) ++nonEmpty;
        }

        if (nonEmpty < 2) return;

        const int correctIndex = mcCorrectGroup->checkedId();
        if (correctIndex < 0 || correctIndex >= choices.size()) {
            return;
        }

        emit back();
        break;
    }
    case 1: { // True/False
        const QString question = tfQuestion->text().trimmed();
        if (question.isEmpty()) return;
        const bool ansTrue = (tfAnswer->currentIndex() == 0);

        emit back();
        break;
    }
    case 2: { // Short Answer
        const QString question = saQuestion->text().trimmed();
        const QString answer   = saAnswer->text().trimmed();
        if (question.isEmpty() || answer.isEmpty()) {
            return;
        }

        emit back();
        break;
    }
    }
}

void EditQuestionMenu::setToEdit(Question* toEdit) {
    toEdit_ = toEdit;

    if (auto mc = dynamic_cast<MCQuestion*>(toEdit)) { // Multi
        typeStack->setCurrentIndex(0);
        mcQuestion->setText(toEdit->getQuestion());

        QStringList choices = mc->getChoices();
        QString correct = mc->getAnswer();

        for (const QString &s : choices) {
            addMCChoiceRow(s, s == correct);
        }

    } else if (auto tf = dynamic_cast<TFQuestion*>(toEdit)) { // TF
        typeStack->setCurrentIndex(1);
        tfQuestion->setText(toEdit->getQuestion());
        if (tf->getAnswer() == "True") {
            tfAnswer->setCurrentIndex(0);
        } else {
            tfAnswer->setCurrentIndex(1);
        }
    } else { // Short
        typeStack->setCurrentIndex(2);
        saQuestion->setText(toEdit->getQuestion());
        saAnswer->setText(toEdit->getAnswer());
    }
}

/*
// True/False
QWidget*   tfPage     = nullptr;
QLineEdit* tfQuestion = nullptr;
QComboBox* tfAnswer   = nullptr;

// Short Answer
QWidget*   saPage     = nullptr;
QLineEdit* saQuestion = nullptr;
QLineEdit* saAnswer   = nullptr;

// Multiple Choice
QWidget*     mcPage          = nullptr;
QLineEdit*   mcQuestion      = nullptr;
QVBoxLayout* mcChoicesLayout = nullptr;
QButtonGroup* mcCorrectGroup = nullptr;
QPushButton* mcAddChoiceBtn  = nullptr; */
