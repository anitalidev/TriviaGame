#ifndef QUESTION_H
#define QUESTION_H

#include <QString>


class Question
{
public:
    virtual ~Question() = default;

    virtual QString getQuestion() const = 0;
    virtual bool checkAnswer(const QString& user) const = 0;
    virtual QString getAnswer() const = 0;

private:
};

#endif // QUESTION_H
