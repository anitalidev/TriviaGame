#ifndef TFQUESTION_H
#define TFQUESTION_H

#include "question.h"

class TFQuestion : public Question {
public:
    TFQuestion(const QString& ask, const QString& correctAnswer);

    QString getQuestion() const override {return ask_; };
    QString getAnswer() const override {return correctAnswer_; };

private:
    QString ask_;
    QString correctAnswer_;
};

#endif // TFQUESTION_H
