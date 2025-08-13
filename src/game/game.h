#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <memory>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "gamesettings.h"
#include "questionbank.h"

class QuestionBank;

class Game : public QWidget {
    Q_OBJECT
public:
    explicit Game(QWidget* parent = nullptr);
    void start();
    void onSubmit();

signals:
    void quit();
    void exitToMenu();

private:
    QuestionBank* bank_;
    Question* currQ_;

    QLabel*     prompt_;
    QLineEdit*  answer_;
    QPushButton* submit_;

    void buildQuestionBank();
    void startRun();
    int lives_;
};

#endif
