#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QHash>
#include <QHashFunctions>
#include <utility>

enum class Page { Menu, Game, Options };

inline uint qHash(Page key, uint seed = 0) noexcept {
    return ::qHash(static_cast<int>(key), seed);
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui = nullptr;

    QStackedWidget* stack_ = nullptr;

    QHash<Page, int> pageIndex_;

    template <typename T>
    T* addPage(Page id) {
        T* w = new T(this);
        int idx = stack_->addWidget(w);
        pageIndex_.insert(id, idx);
        return w;
    }

    void goTo(Page id) {
        if (pageIndex_.contains(id)) {
            stack_->setCurrentIndex(pageIndex_.value(id));
        }
    }
};

#endif
