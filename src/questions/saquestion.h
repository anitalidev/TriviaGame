#ifndef SAQUESTION_H
#define SAQUESTION_H

#include "question.h"
#include <vector>
#include <cstddef>

class SAQuestion : public Question {
public:
    SAQuestion(const QString& ask, const QString& correctAnswer);

    QString getQuestion() const override {return ask_; };
    QString getAnswer() const override {return correctAnswer_; };

private:
    QString ask_;
    QString correctAnswer_;
};

#endif // MCQUESTION_H
