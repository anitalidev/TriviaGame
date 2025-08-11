#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MainMenu.h"
#include "Game.h"
#include "optionsmenu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    stack_ = new QStackedWidget(this);
    setCentralWidget(stack_);

    MainMenu* menu    = addPage<MainMenu>(Page::Menu);
    Game* game    = addPage<Game>(Page::Game);
    OptionsMenu* options = addPage<OptionsMenu>(Page::Options);

    connect(menu, &MainMenu::start, this, [this]{
        goTo(Page::Game);
    });
    connect(menu, &MainMenu::options, this, [this]{
        goTo(Page::Options);
    });

    connect(game, &Game::back, this, [this]{
        goTo(Page::Menu);
    });
    connect(options, &OptionsMenu::back, this, [this]{
        goTo(Page::Menu);
    });

    goTo(Page::Menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
