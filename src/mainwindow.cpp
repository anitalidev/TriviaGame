#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MainMenu.h"
#include "Game.h"
#include "optionsmenu.h"
#include "ManageQuestionsMenu.h"
#include "AddQuestionMenu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    stack_ = new QStackedWidget(this);
    setCentralWidget(stack_);

    MainMenu* menu    = addPage<MainMenu>(Page::Menu);
    Game* game    = addPage<Game>(Page::Game);
    OptionsMenu* options = addPage<OptionsMenu>(Page::Options);
    ManageQuestionsMenu* manageQuestions = addPage<ManageQuestionsMenu>(Page::ManageQuestions);
    AddQuestionMenu* addQuestion = addPage<AddQuestionMenu>(Page::AddQuestion);

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
    connect(options, &OptionsMenu::manageQuestions, this, [this]() {
        goTo(Page::ManageQuestions);
    });

    connect(manageQuestions, &ManageQuestionsMenu::addQuestion, this, [this]() {
        goTo(Page::AddQuestion);
    });

    connect(addQuestion, &AddQuestionMenu::submit, this,
            [this, manageQuestions](QString type, QString q, QString a) {
                // Create a Question object based on type & add to QuestionBank
                // Then refresh manageQuestions->setQuestions(...)
                goTo(Page::ManageQuestions);
            });

    connect(manageQuestions, &ManageQuestionsMenu::back, this, [this]() {
        goTo(Page::Options);
    });

    connect(addQuestion, &AddQuestionMenu::cancel, this, [this]() {
        goTo(Page::ManageQuestions);
    });


    goTo(Page::Menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
