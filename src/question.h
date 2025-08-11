#ifndef QUESTION_H
#define QUESTION_H

#include <string>


class Question
{
public:
    virtual ~Question() = default;

    virtual std::string getQuestion() const = 0;
    virtual std::string getAnswer() const = 0;

private:
};

#endif // QUESTION_H
