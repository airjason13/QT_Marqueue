#ifndef LEDSHOWA_H
#define LEDSHOWA_H

#include <QWidget>

namespace Ui {
class ledshowa;
}

class ledshowa : public QWidget
{
    Q_OBJECT

public:
    explicit ledshowa(QWidget *parent = nullptr);
    ~ledshowa();

private:
    Ui::ledshowa *ui;
};

#endif // LEDSHOWA_H
