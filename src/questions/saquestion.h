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
    bool checkAnswer(const QString& user) const override {return correctAnswer_ == user; };
    std::unique_ptr<Question> clone() const  override {
        return std::make_unique<SAQuestion>(*this);
    }

private:
    QString ask_;
    QString correctAnswer_;
};

#endif // MCQUESTION_H
