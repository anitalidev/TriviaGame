#ifndef MCQUESTION_H
#define MCQUESTION_H

#include "question.h"
#include <QStringList>
#include <cstddef>

class MCQuestion : public Question {
public:
    MCQuestion(const QString& ask, QStringList& choices, const std::size_t correctIndex);

    QString getQuestion() const override {return ask_; };
    QString getAnswer() const override {return choices_[correctIndex_]; };
    bool checkAnswer(const QString& user) const override {return choices_[correctIndex_] == user; };
    std::unique_ptr<Question> clone() const  override {
        return std::make_unique<MCQuestion>(*this);
    }

    const QStringList& getChoices() const noexcept;

    std::size_t correctIndex() const noexcept {return correctIndex_; };
    std::size_t correctLabel() const noexcept {return correctIndex_ + 1; };

private:
    QString ask_;
    mutable QStringList choices_;
    mutable std::size_t correctIndex_;
};

#endif // MCQUESTION_H
