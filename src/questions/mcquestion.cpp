#include "mcquestion.h"

// REQUIRES: choices is not empty, correctIndex < choices.size() < 11
MCQuestion::MCQuestion(const QString& ask, QStringList& choices, const std::size_t correctIndex) {
    ask_ = ask;
    choices_ = choices;
    correctIndex_ = correctIndex;
}


