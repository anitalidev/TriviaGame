#ifndef MANAGEQUESTIONSMENU_H
#define MANAGEQUESTIONSMENU_H

#include <QWidget>
#include <QStringList>

class QListWidget;
class QPushButton;

class ManageQuestionsMenu : public QWidget {
    Q_OBJECT

public:
    explicit ManageQuestionsMenu(QWidget* parent = nullptr);

    void setQuestions(const QStringList& items);

signals:
    void back();
    void addQuestion();
    void remove(int index);

private:
    QListWidget* questionList_;
    QPushButton* removeButton_;
};

#endif // MANAGEQUESTIONSMENU_H
