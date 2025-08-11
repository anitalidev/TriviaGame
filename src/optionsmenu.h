#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QWidget>

class OptionsMenu : public QWidget
{

    Q_OBJECT

public:
    explicit OptionsMenu(QWidget* parent = nullptr);

signals:
    void back();


};

#endif // OPTIONSMENU_H
