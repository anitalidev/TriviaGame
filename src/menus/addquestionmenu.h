#ifndef ADDQUESTIONMENU_H
#define ADDQUESTIONMENU_H

#pragma once

#include <QWidget>

class QLineEdit;
class QComboBox;

class AddQuestionMenu : public QWidget
{

    Q_OBJECT

public:
    explicit AddQuestionMenu(QWidget* parent = nullptr);

private:
    QComboBox* typeBox;
    QLineEdit* questionEdit;
    QLineEdit* answerEdit;

signals:
    void submit(QString type, QString q, QString a);
    void cancel();
};

#endif // ADDQUESTIONMENU_H
