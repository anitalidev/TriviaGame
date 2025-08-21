#ifndef EDITQUESTIONMENU_H
#define EDITQUESTIONMENU_H

#include <QWidget>
#include <QStringList>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "question.h"

class EditQuestionMenu : public QWidget
{

    Q_OBJECT

public:
    explicit EditQuestionMenu(QWidget* parent = nullptr);
    void setToEdit(Question* toEdit);

private:
    QComboBox*      typeBox      = nullptr;
    QStackedWidget* typeStack    = nullptr;
    QPushButton*    backButton   = nullptr;
    QPushButton*    submitButton = nullptr;

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
    QPushButton* mcAddChoiceBtn  = nullptr;

    void addMCChoiceRow(const QString& text = QString(), bool checked = false);
    void submitCurrent();

    Question* toEdit_;

signals:
    void back();
};

#endif // EDITQUESTIONMENU_H
