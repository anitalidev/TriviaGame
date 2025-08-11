#ifndef SAQUESTION_H
#define SAQUESTION_H

#include "Question.h"
#include <string>
#include <vector>
#include <cstddef>

class SAQuestion : public Question {
public:
    SAQuestion(std::string ask, std::string correctAnswer);

    std::string getQuestion() const override {return ask_; };
    std::string getAnswer() const override {return correctAnswer_; };

private:
    std::string ask_;
    std::string correctAnswer_;
};

#endif // MCQUESTION_H
