#include "questionbank.h"

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
}

bool QuestionBank::questionsComplete() {
    return index_ >= count_;
}

// REQUIRES: !questionsComplete();
Question* QuestionBank::nextQuestion() {
    if (questionsComplete()) {
        return nullptr;
    }
    return questions_[index_++].get();
}
