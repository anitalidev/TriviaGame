#include "mcquestion.h"

#include <algorithm>
#include <random>

// REQUIRES: choices is not empty, correctIndex < choices.size() < 11
MCQuestion::MCQuestion(const QString& ask, QStringList& choices, const std::size_t correctIndex) {
    ask_ = ask;
    choices_ = choices;
    correctIndex_ = correctIndex;
}


const QStringList& MCQuestion::getChoices() const noexcept {
    // Keep track of the original correct answer
    QString correctAnswer = choices_[correctIndex_];

    // Shuffle
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::shuffle(choices_.begin(), choices_.end(), rng);

    // Update correctIndex_ to match the shuffled position of the correct answer
    auto it = std::find(choices_.begin(), choices_.end(), correctAnswer);
    correctIndex_ = std::distance(choices_.begin(), it);

    return choices_;
}
