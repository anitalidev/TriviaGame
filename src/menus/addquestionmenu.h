#ifndef ADDQUESTIONMENU_H
#define ADDQUESTIONMENU_H

#include <QWidget>
#include <QStringList>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QButtonGroup>

class AddQuestionMenu : public QWidget {
    Q_OBJECT
public:
    explicit AddQuestionMenu(QWidget* parent = nullptr);

signals:
    void cancel();

    void submitTF(const QString& question, bool answerTrue);
    void submitSA(const QString& question, const QString& answer);
    void submitMC(const QString& question, const QStringList& choices, int correctIndex);
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
};

#endif // ADDQUESTIONMENU_H
