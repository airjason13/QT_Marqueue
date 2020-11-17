#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "ledscreen.h"
#define printf qDebug

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ClickShowButton();
    void ClickCloseButton();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    void test();

private slots:
    void timer_timeout();

signals:
    void startbuttonclicked(QString str);
    void stopbuttonclicked();
};
#endif // MAINWINDOW_H
