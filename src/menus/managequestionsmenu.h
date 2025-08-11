#ifndef MANAGEQUESTIONSMENU_H
#define MANAGEQUESTIONSMENU_H

#include <QWidget>

class ManageQuestionsMenu : public QWidget
{

    Q_OBJECT

public:
    explicit ManageQuestionsMenu(QWidget* parent = nullptr);

signals:
    void back();
    void addQuestion();
};

#endif // MANAGEQUESTIONSMENU_H
