#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainmenu.h"
#include "game.h"
#include "gameoptionsmenu.h"
#include "optionsmenu.h"
#include "managequestionsmenu.h"
#include "addquestionmenu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    questions_ = new QuestionBank(std::vector<std::unique_ptr<Question>>());
    addSampleQuestions(*questions_); // FOR TESTING ONLY
    g_settings.questions = questions_;

    ui->setupUi(this);

    stack_ = new QStackedWidget(this);
    setCentralWidget(stack_);

    Game* game    = addPage<Game>(Page::Game);
    MainMenu* menu    = addPage<MainMenu>(Page::Menu);
    GameOptionsMenu* gameOptions    = addPage<GameOptionsMenu>(Page::GameOptionsMenu);
    OptionsMenu* options = addPage<OptionsMenu>(Page::Options);
    ManageQuestionsMenu* manageQuestions = addPage<ManageQuestionsMenu>(Page::ManageQuestions);
    AddQuestionMenu* addQuestion = addPage<AddQuestionMenu>(Page::AddQuestion);

    manageQuestions->setQuestions(*questions_);

    // User wants to start game
    connect(menu, &MainMenu::start, this, [this]{
        goTo(Page::GameOptionsMenu);
    });

    // User wants to see options/settings
    connect(menu, &MainMenu::options, this, [this]{
        goTo(Page::Options);
    });

    // User wants to go back from game to main menu
    connect(gameOptions, &GameOptionsMenu::back, this, [this]{
        goTo(Page::Menu);
    });

    // User wants to go back from options to main menu
    connect(options, &OptionsMenu::back, this, [this]{
        goTo(Page::Menu);
    });

    // User wants to view/add/remove questions
    connect(options, &OptionsMenu::manageQuestions, this, [this]() {
        goTo(Page::ManageQuestions);
    });

    // User wants to add a question
    connect(manageQuestions, &ManageQuestionsMenu::addQuestion, this, [this]() {
        goTo(Page::AddQuestion);
    });

    // User is adding a question
    connect(addQuestion, &AddQuestionMenu::submit, this,
            [this, manageQuestions](QString type, QString q, QString a) {
            // types: "Multiple Choice", "True/False", "Short Answer"
            std::unique_ptr<Question> newQuestion;
            if (type == "Multiple Choice") {
                QStringList list = a.split(",", Qt::SkipEmptyParts);

                newQuestion = std::make_unique<MCQuestion>(q, list, 0);


            } else if (type == "True/False") {
                QString tf(a == "True" ? "True" : "False");
                newQuestion = std::make_unique<TFQuestion>(q, tf);
            } else {
                newQuestion = std::make_unique<SAQuestion>(q, a);
            }

            questions_->addQuestion(std::move(newQuestion));
            manageQuestions->setQuestions(*questions_);

                goTo(Page::ManageQuestions);
            });

    // User would like to go back from managing questions to options
    connect(manageQuestions, &ManageQuestionsMenu::back, this, [this]() {
        goTo(Page::Options);
    });

    // User would like to start the game
    connect(gameOptions, &GameOptionsMenu::startRequested, this, [this]() {
        goTo(Page::Game);
    });

    // User would like to quit the game
    connect(game, &Game::quit, this, [this]() {
        goTo(Page::GameOptionsMenu);
    });

    // User would no longer like to add a qusetion
    connect(addQuestion, &AddQuestionMenu::cancel, this, [this]() {
        goTo(Page::ManageQuestions);
    });

    // User would like to remove a question
    connect(manageQuestions, &ManageQuestionsMenu::remove, this, [this, manageQuestions](int idx){
        questions_->removeQuestion(idx);
        manageQuestions->setQuestions(*questions_);
    });


    goTo(Page::Menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSampleQuestions(QuestionBank& questionBank) { // FOR TESTING ONLY

    QStringList mc1Choices = {"Mercury", "Venus", "Earth", "Mars"};
    questionBank.addQuestion(std::make_unique<MCQuestion>(
        "Which planet is known as the Red Planet?",
        mc1Choices,
        3
        ));

    QStringList mc2Choices = {"4", "5", "6", "7"};
    questionBank.addQuestion(std::make_unique<MCQuestion>(
        "What is 2 + 2",
        mc2Choices,
        0
        ));

    questionBank.addQuestion(std::make_unique<SAQuestion>(
        "What is the capital of France?",
        "Paris"
        ));

    questionBank.addQuestion(std::make_unique<SAQuestion>(
        "Who wrote 'Romeo and Juliet'?",
        "William Shakespeare"
        ));

    questionBank.addQuestion(std::make_unique<TFQuestion>(
        "The Sun is a star.",
        "True"
        ));

    questionBank.addQuestion(std::make_unique<TFQuestion>(
        "Bats are birds.",
        "False"
        ));
}
