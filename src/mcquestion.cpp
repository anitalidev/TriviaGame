#include "mcquestion.h"

// REQUIRES: choices is not empty, correctIndex < choices.size() < 11
MCQuestion::MCQuestion(std::string ask, std::vector<std::string> choices, std::size_t correctIndex) {
    ask_ = ask;
    choices_ = choices;
    correctIndex_ = correctIndex;
}


