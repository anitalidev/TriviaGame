#ifndef TFQUESTION_H
#define TFQUESTION_H

#include "question.h"

class TFQuestion : public Question {
public:
    TFQuestion(const QString& ask, bool correctAnswer);

    QString getQuestion() const override { return ask_; };

    QString getAnswer() const override { return correctAnswer_ ? "True" : "False"; };

    bool checkAnswer(const QString& user) const override;

    std::unique_ptr<Question> clone() const override {
        return std::make_unique<TFQuestion>(*this);
    }

private:
    QString ask_;
    bool correctAnswer_;
};

#endif // TFQUESTION_H
