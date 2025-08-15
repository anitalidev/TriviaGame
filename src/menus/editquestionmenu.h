#ifndef EDITQUESTIONMENU_H
#define EDITQUESTIONMENU_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include "question.h"

class EditQuestionMenu : public QWidget
{

    Q_OBJECT

public:
    explicit EditQuestionMenu(QWidget* parent = nullptr);
    void setToEdit(Question* toEdit);

private:
    QComboBox* typeBox;
    QLineEdit* questionEdit;
    QLineEdit* answerEdit;

    Question* toEdit_;

signals:
    void back();
};

#endif // EDITQUESTIONMENU_H
