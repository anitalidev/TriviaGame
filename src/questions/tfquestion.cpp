#include "tfquestion.h"

TFQuestion::TFQuestion(const QString& ask, const bool correctAnswer) {
    ask_ = ask;
    correctAnswer_ = correctAnswer;
}

bool TFQuestion::checkAnswer(const QString& user) const {
    QString normalized = user.trimmed().toLower();
    return (correctAnswer_ && normalized == "true") || (!correctAnswer_ && normalized == "false");
}
