#ifndef RULEWINDOW_H
#define RULEWINDOW_H

#include <QMainWindow>

namespace Ui {
class RuleWindow;
}

class RuleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RuleWindow(QWidget *parent = nullptr);
    ~RuleWindow();

private:
    Ui::RuleWindow *ui;
};

#endif // RULEWINDOW_H
