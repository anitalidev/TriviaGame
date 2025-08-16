#include "mcquestion.h"

#include <algorithm>
#include <random>

// REQUIRES: choices is not empty
MCQuestion::MCQuestion(const QString& ask, QStringList& choices, const std::size_t correctIndex) {
    ask_ = ask;
    choices_ = choices;
    correctIndex_ = correctIndex;
}


const QStringList& MCQuestion::getChoices() const noexcept {
    QString correctAnswer = choices_[correctIndex_];

    static thread_local std::mt19937 rng{std::random_device{}()};
    std::shuffle(choices_.begin(), choices_.end(), rng);

    auto it = std::find(choices_.begin(), choices_.end(), correctAnswer);
    correctIndex_ = std::distance(choices_.begin(), it);

    return choices_;
}
