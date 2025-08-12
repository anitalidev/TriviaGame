#include "questionbank.h"

QuestionBank::QuestionBank(std::vector<std::unique_ptr<Question>> questions) {
    questions_ = std::move(questions);
}


void QuestionBank::addQuestion(std::unique_ptr<Question> newQuestion) {
    questions_.push_back(std::move(newQuestion));
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
