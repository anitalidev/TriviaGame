#include "addquestionmenu.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QRadioButton>
#include <QLabel>

AddQuestionMenu::AddQuestionMenu(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* topForm = new QFormLayout;
    typeBox = new QComboBox(this);
    typeBox->addItems({"Multiple Choice", "True/False", "Short Answer"});
    topForm->addRow("Type:", typeBox);
    mainLayout->addLayout(topForm);

    typeStack = new QStackedWidget(this);
    mainLayout->addWidget(typeStack);

    // Multiple Choice
    mcPage = new QWidget(this);
    {
        QFormLayout* mcForm = new QFormLayout(mcPage);
        mcQuestion = new QLineEdit(mcPage);
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

        mcForm->addRow(new QLabel("Choices (select the correct one):", mcPage));
        mcForm->addRow(choicesBox);
        mcForm->addRow("", mcAddChoiceBtn);

        addMCChoiceRow();
        addMCChoiceRow();
        if (auto* first = mcCorrectGroup->button(0)) first->setChecked(true);
    }
    typeStack->addWidget(mcPage); // 0

    // True/False
    tfPage = new QWidget(this);
    {
        auto* tfForm = new QFormLayout(tfPage);
        tfQuestion = new QLineEdit(tfPage);
        tfAnswer   = new QComboBox(tfPage);
        tfAnswer->addItems({"True", "False"});

        tfForm->addRow("Question:", tfQuestion);
        tfForm->addRow("Answer:",   tfAnswer);
    }
    typeStack->addWidget(tfPage); // 1

    // Short Answer
    saPage = new QWidget(this);
    {
        QFormLayout* saForm = new QFormLayout(saPage);
        saQuestion = new QLineEdit(saPage);
        saAnswer   = new QLineEdit(saPage);
        saForm->addRow("Question:", saQuestion);
        saForm->addRow("Answer:",   saAnswer);
    }
    typeStack->addWidget(saPage); // 2

    connect(typeBox, qOverload<int>(&QComboBox::currentIndexChanged),
            typeStack, &QStackedWidget::setCurrentIndex);
    typeStack->setCurrentIndex(0);

    QHBoxLayout* buttons = new QHBoxLayout;
    backButton   = new QPushButton("Back", this);
    submitButton = new QPushButton("Submit", this);
    buttons->addWidget(backButton);
    buttons->addStretch();
    buttons->addWidget(submitButton);
    mainLayout->addLayout(buttons);

    connect(backButton, &QPushButton::clicked, this, &AddQuestionMenu::cancel);
    connect(submitButton, &QPushButton::clicked, this, &AddQuestionMenu::submitCurrent);
}

void AddQuestionMenu::addMCChoiceRow(const QString& text, bool checked) {
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

void AddQuestionMenu::submitCurrent() {
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

        emit submitMC(question, choices, correctIndex);
        break;
    }
    case 1: { // True/False
        const QString question = tfQuestion->text().trimmed();
        if (question.isEmpty()) return;
        const bool ansTrue = (tfAnswer->currentIndex() == 0);

        emit submitTF(question, ansTrue);
        break;
    }
    case 2: { // Short Answer
        const QString question = saQuestion->text().trimmed();
        const QString answer   = saAnswer->text().trimmed();
        if (question.isEmpty() || answer.isEmpty()) {
            return;
        }

        emit submitSA(question, answer);
        break;
    }
    }
}
