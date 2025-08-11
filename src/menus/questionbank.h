#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include "question.h"
#include <vector>
#include <memory>

class QuestionBank
{
public:
    QuestionBank(std::vector<std::unique_ptr<Question>> questions);

    const std::vector<std::unique_ptr<Question>>& getQuestions() const { return questions_; }
    void addQuestion(std::unique_ptr<Question> newQuestion);

private:
    std::vector<std::unique_ptr<Question>> questions_;
};

#endif // QUESTIONBANK_H
