#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainmenu.h"
#include "game.h"
#include "optionsmenu.h"
#include "managequestionsmenu.h"
#include "addquestionmenu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    questions_ = new QuestionBank(std::vector<std::unique_ptr<Question>>());

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

    connect(manageQuestions, &ManageQuestionsMenu::back, this, [this]() {
        goTo(Page::Options);
    });

    connect(addQuestion, &AddQuestionMenu::cancel, this, [this]() {
        goTo(Page::ManageQuestions);
    });

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
