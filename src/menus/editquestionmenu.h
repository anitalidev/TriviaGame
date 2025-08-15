#ifndef EDITQUESTIONMENU_H
#define EDITQUESTIONMENU_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>

class EditQuestionMenu : public QWidget
{

    Q_OBJECT

public:
    explicit EditQuestionMenu(QWidget* parent = nullptr);

private:
    QComboBox* typeBox;
    QLineEdit* questionEdit;
    QLineEdit* answerEdit;

signals:
    void back();
};

#endif // EDITQUESTIONMENU_H
