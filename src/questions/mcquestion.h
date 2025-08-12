#ifndef MCQUESTION_H
#define MCQUESTION_H

#include "question.h"
#include <QStringList>
#include <vector>
#include <cstddef>

class MCQuestion : public Question {
public:
    MCQuestion(const QString& ask, QStringList& choices, const std::size_t correctIndex);

    QString getQuestion() const override {return ask_; };
    QString getAnswer() const override {return choices_[correctIndex_]; };
    const QStringList& getChoices() const noexcept { return choices_; };

    std::size_t correctIndex() const noexcept {return correctIndex_; };
    std::size_t correctLabel() const noexcept {return correctIndex_ + 1; };

private:
    QString ask_;
    QStringList choices_;
    std::size_t correctIndex_;
};

#endif // MCQUESTION_H
