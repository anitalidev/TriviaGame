#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QWidget>
#include "questionbank.h"

class OptionsMenu : public QWidget
{

    Q_OBJECT

public:
    explicit OptionsMenu(QWidget* parent = nullptr);

signals:
    void back();
    void manageQuestions();
};

#endif // OPTIONSMENU_H
