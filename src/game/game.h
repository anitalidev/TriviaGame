#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <memory>
#include "gamesettings.h"

class QuestionBank;

class Game : public QWidget {
    Q_OBJECT
public:
    explicit Game(QWidget* parent = nullptr);
    void start();

signals:
    void quit();
    void exitToMenu();

private:
    GameSettings settings_;
    QuestionBank* bank_;
    void buildQuestionBank();
    void startRun();
    int lives_;
};

#endif
