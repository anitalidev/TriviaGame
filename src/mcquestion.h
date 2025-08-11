#ifndef MCQUESTION_H
#define MCQUESTION_H

#include "Question.h"
#include <string>
#include <vector>
#include <cstddef>

class MCQuestion : public Question {
public:
    MCQuestion(std::string ask, std::vector<std::string> choices, std::size_t correctIndex);

    std::string getQuestion() const override {return ask_; };
    std::string getAnswer() const override {return choices_[correctIndex_]; };
    const std::vector<std::string>& getChoices() const noexcept { return choices_; };

    std::size_t correctIndex() const noexcept {return correctIndex_; };
    std::size_t correctLabel() const noexcept {return correctIndex_ + 1; };

private:
    std::string ask_;
    std::vector<std::string> choices_;
    std::size_t correctIndex_;
};

#endif // MCQUESTION_H
