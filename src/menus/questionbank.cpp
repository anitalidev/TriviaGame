#include "questionbank.h"

#include <random>
#include <algorithm>

QuestionBank::QuestionBank(std::vector<std::unique_ptr<Question>> questions) {
    index_ = 0;
    count_ = questions.size();
    questions_ = std::move(questions);
}


void QuestionBank::addQuestion(std::unique_ptr<Question> newQuestion) {
    questions_.push_back(std::move(newQuestion));
    ++count_;
}

void QuestionBank::removeQuestion(std::size_t index) {
    if (index < questions_.size()) {
        questions_.erase(questions_.begin() + index);
    }
}

QStringList QuestionBank::toQStringList() const {
    QStringList list;
    for (const auto& q : questions_) {
        list << q->getQuestion();
    }
    return list;
}

bool QuestionBank::isEmpty() const {
    return questions_.empty();
}

void QuestionBank::setUp(bool shuffle) {
    index_ = 0;
    shuffle_ = shuffle;
    if (shuffle) {
        std::vector<std::unique_ptr<Question>> shuffledQuestions;
        shuffledQuestions.reserve(questions_.size());
        for (const auto& q : questions_) {
            shuffledQuestions.push_back(q->clone());
        }

        static thread_local std::mt19937 g{std::random_device{}()};

        std::shuffle(shuffledQuestions.begin(), shuffledQuestions.end(), g);
        shuffledQuestions_ = std::move(shuffledQuestions);
    }
}

bool QuestionBank::questionsComplete() {
    return index_ >= count_;
}

// REQUIRES: !questionsComplete();
Question* QuestionBank::nextQuestion() {
    if (questionsComplete()) {
        return nullptr;
    }
    if (shuffle_) {
        return shuffledQuestions_[index_++].get();
    }
    return questions_[index_++].get();
}

Question* QuestionBank::getQuestion(int index) {
    return questions_[index].get();
}
