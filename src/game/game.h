#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <memory>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "gamesettings.h"
#include "questionbank.h"

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
    QuestionBank* bank_;
    Question* currQ_;

    QLabel*     prompt_;
    QVBoxLayout*  answer_;
    QPushButton* submit_;

    void clearLayout(QLayout* layout);

    void onSubmit(const QString& text);

    void buildQuestionBank();
    void startRun();
    int lives_;
    bool shuffle_;
};

#endif
