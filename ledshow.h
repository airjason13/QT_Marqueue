#ifndef LEDSHOW_H
#define LEDSHOW_H

#include <QWidget>
#include <QDebug>
#define printf qDebug

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

public slots:
    void accept();

private:
    Ui::Form *ui;
};

#endif // LEDSHOW_H
