#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#pragma once
#include <QString>

class QuestionBank;

struct GameSettings {
    int lives = 3;
    bool shuffle = true;
    QString playerName;
    QuestionBank* questions;
};

extern GameSettings g_settings;

#endif
